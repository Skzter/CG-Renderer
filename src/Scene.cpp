#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/Scene.hpp"
#include <cstddef>
#include <exception>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <thread>

template<class T>
T getOption(std::istream& in, std::string option){
	T value;
	std::string line;
	std::getline(in,line);
	size_t pos;
	if((pos = line.find(option)) != std::string::npos){
		//std::cout << pos << std::endl;
		std::istringstream op(line.substr(pos + option.length()));
		op >> value;
	}
	else {
		throw std::runtime_error("Option \"" + option + "\" not found");
	}
	return value;
}

void skip(unsigned int ignoreLines, std::istream& file){
	for(unsigned short i = 0; i < ignoreLines; i++)
		file.ignore	(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Scene::loadFile(std::istream& file){
	std::string line;
	int numvert;
	int numface;

	skip(2, file); //skip format
	numvert = getOption<int>(file, "element vertex");
	skip(3,file); //just use float
	numface = getOption<int>(file, "element face");
	skip(1,file); //??

	do{
		file >> line;
	}while(line != "end_header");

	//Auch einfach vertrauen das alle dimensionen richig sind
	//vertices
	std::vector<Vector3D> vertices;
	vertices.reserve(numvert);
	std::vector<std::vector<int>> faces;
	faces.reserve(numface);

	short dimensionen = 3;
	float cords[3];
	float cord;
	for(size_t curvert = 0; curvert < numvert; curvert++){
		for(size_t dim = 0; dim < dimensionen; dim++){
			file >> cord;
			cords[dim] = cord;
		}
		vertices.push_back(Vector3D(cords[0],cords[1],cords[2]));
	}

	short vertpos;
	for(size_t face = 0; face < numface; face++){
		int numvert;
		file >> numvert;
		std::vector<int> verts(numvert);

		for(size_t curvert = 0; curvert < numvert; curvert++){
			file >> vertpos;
			verts.at(curvert) = (vertpos);
		}

		if(numvert > 3){
			int i = 1;
			while(i < numvert - 1){
				faces.push_back({verts.at(0),verts.at(i++),verts.at(i)});
			}
		}else{
			faces.push_back(verts);
		}
	}
	this->Object3Ds.push_back(Object3D(vertices,faces));
}

void Scene::calcPixels(BinaryDisect* disect,size_t startH, size_t endH, float pixelWidth, float pixelHeight, uint8_t* buffer, Vector3D VecToOrigin){
	if(startH > endH || startH < 0 || endH > camera.height_pixels)
		return;
	for (size_t curH = startH; curH < endH; curH++)
	{
		for (size_t curW = 0; curW < camera.width_pixels; curW++)
		{
			if(curH % 10 == 0 && curW == 0){
				proglock.lock();
				std::cout << ((++progress) * 1000) / camera.height_pixels << "%" << std::endl;
				proglock.unlock();
			}
			Ray ray = Ray(camera.eye, VecToOrigin + Vector3D(((float)curW) * pixelWidth, -(((float)curH) * pixelHeight), 0));
			Hitpoint closest = disect->closestHitpoint(ray);
			
			Color col;
			if(closest.face != nullptr)
			{
				//std::cout << "Treffer!\n";
				col = closest.face->texture.color;
			} else 
			{
				col = Color();
			}
			size_t pos = curH * camera.width_pixels + curW;
			buffer[pos * 3] = col.getr();     // Red
			buffer[pos * 3 + 1] = col.getg(); // Green
			buffer[pos * 3 + 2] = col.getb();// Blue
			//std::cout << pos * 3 << " R: " << (int)buffer[pos * 3] << std::endl;
			//std::cout << pos * 3 + 1 << " G: " << (int)buffer[pos * 3 + 1] << std::endl;
			//std::cout << pos * 3 + 2 << " B: " << (int)buffer[pos * 3 + 2] << std::endl;
			//std::cout << "------------" << std::endl;
			// origin plus punkt nach rechts - punkt aus i,j,0
			// aus i j verhältnis zu bildschirm und dann gänsehosen
		}
	}
}

void Scene::testoptimized(BoundingBox box, int depth){
	std::vector<Face3D*> allfaces;
	for (Object3D& object : Object3Ds){
		for(int i = 0; i < object.getFaces().size(); i++){
			Face3D* face = &(object.getFaces().at(i));
			allfaces.push_back(face);
		}
	}
	
	BinaryDisect* disect = BinaryDisect::createNode(allfaces, depth, box);
	std::cout << "Most Faces: " << BinaryDisect::mostFaces << std::endl;

	std::cout << "Start Drawing" << std::endl;
	uint8_t *buffer = new uint8_t[camera.width_pixels * camera.height_pixels * 3];
	Vector3D vectorToOriginPixel = camera.view + Vector3D(-(camera.width/2),camera.height/2,0);
	float pixelWidth = camera.width / camera.width_pixels;
	float pixelHeight = camera.height / camera.height_pixels;
	
	const size_t numThreads = 8;
	std::vector<std::thread> threads;
	const size_t rowsPerThread = camera.height_pixels / numThreads;
	progress = 0;

	for(size_t i = 0; i < numThreads; i++){
		size_t startH = i * rowsPerThread;
        size_t endH = (i == numThreads - 1) ? camera.height_pixels : startH + rowsPerThread;

		threads.push_back(std::thread(&Scene::calcPixels, this, disect,startH,endH, pixelWidth, pixelHeight, buffer, vectorToOriginPixel));
	}

	//calcPixels(disect,0,camera.height_pixels/2, pixelWidth, pixelHeight, buffer, vectorToOriginPixel);
	//calcPixels,disect,camera.height_pixels / 2 - 1,camera.height_pixels, pixelWidth, pixelHeight, buffer, vectorToOriginPixel

	for(auto& t : threads){
		t.join();
	}

	disect->dealoc();

	int success = stbi_write_png("output_opt.png", camera.width_pixels, camera.height_pixels, 3, buffer, camera.width_pixels * 3);
	delete[] buffer;

	if (!success)
	{
		std::cout << "Failed to write PNG!" << std::endl;
		return;
	}
	// 2d array von colors pro pixel zu 1D array mit rgb values 
}

void Scene::drawPicture()
{
    uint8_t *buffer = new uint8_t[camera.width_pixels * camera.height_pixels * 3];
	Vector3D vectorToOriginPixel = camera.view + Vector3D(-(camera.width/2),camera.height/2,0);
	float pixelWidth = camera.width / camera.width_pixels;
	float pixelHeight = camera.height / camera.height_pixels;
	for (size_t curH = 0; curH < camera.height_pixels; curH++)
	{
		for (size_t curW = 0; curW < camera.width_pixels; curW++)
		{
			std::cout << curH << " " << curW << std::endl;
			Ray ray = Ray(camera.eye, vectorToOriginPixel + Vector3D(((float)curW) * pixelWidth, -(((float)curH) * pixelHeight), 0));
			//std::cout << "Ray - origin: " << ray.origin << " direction: " << ray.direction << "\n";
			Hitpoint defaultHitpoint = Hitpoint();
			for (Object3D& object : Object3Ds)
			{
				for (Face3D face : object.getFaces())
				{
					Hitpoint hit = ray.check(face);
					if (hit.distance < defaultHitpoint.distance)
					{
						defaultHitpoint = hit;
					}
				}
			}
			Color col;
			if(defaultHitpoint.face != nullptr)
			{
				//std::cout << "Treffer!\n";
				col = defaultHitpoint.face->texture.color;
			} else 
			{
				col = Color();
			}
			size_t pos = curH * camera.width_pixels + curW;
			buffer[pos * 3] = col.getr();     // Red
			buffer[pos * 3 + 1] = col.getg(); // Green
			buffer[pos * 3 + 2] = col.getb();// Blue
			//std::cout << pos * 3 << " R: " << (int)buffer[pos * 3] << std::endl;
			//std::cout << pos * 3 + 1 << " G: " << (int)buffer[pos * 3 + 1] << std::endl;
			//std::cout << pos * 3 + 2 << " B: " << (int)buffer[pos * 3 + 2] << std::endl;
			//std::cout << "------------" << std::endl;
			// origin plus punkt nach rechts - punkt aus i,j,0
			// aus i j verhältnis zu bildschirm und dann gänsehosen
		}
	}

	int success = stbi_write_png("output.png", camera.width_pixels, camera.height_pixels, 3, buffer, camera.width_pixels * 3);
	delete[] buffer;

	if (!success)
	{
		std::cerr << "Failed to write PNG!" << std::endl;
		return;
	}
	// 2d array von colors pro pixel zu 1D array mit rgb values 
}

Scene::Scene(){	
}