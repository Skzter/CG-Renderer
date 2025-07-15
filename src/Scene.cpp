#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iterator>
#include <ostream>
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


int IBinaryDisect::mostFaces = 0;
int IBinaryDisect::sumFaces = 0;
int IBinaryDisect::cntLeafs = 0;

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

void Scene::loadFile(std::istream& file, int depth){
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

    //beschleunigung
    BoundingBox box = BoundingBox{Vector3D::maxVector, Vector3D::minVector};

    std::vector<Face3D*> allfaces;
    for (Object3D& object : Object3Ds){
	size_t size = object.getFaces().size();
	for(int i = 0; i < size; i++){
	    Face3D* face = &(object.getFaces().at(i));
	    allfaces.push_back(face);
	}
	// Boundingbox berechnen
	for(Vector3D p : object.getPoints()){
	    for(int j = 0; j < 3; j++){
		if(p.at(j) < box.p1.at(j)){
		    box.p1.at(j) = p.at(j);
		}
		if(p.at(j) > box.p2.at(j)){
		    box.p2.at(j) = p.at(j);
		}
	    }
	}
    }

    std::cout << "Box: " << box.p1 << box.p2 << std::endl;

    IBinaryDisect::mostFaces = 0;
    IBinaryDisect::sumFaces = 0;
    IBinaryDisect::cntLeafs = 0;

    //IBinaryDisect* disect = new BinaryArray(allfaces, depth, box);
    //IBinaryDisect* disect = BinaryDisect::createNode(allfaces, depth, box);
    IBinaryDisect* disect = new MixedArray(allfaces, depth, box);

    std::cout << "Most Faces: " << IBinaryDisect::mostFaces << std::endl;
    std::cout << "Avg Faces: " << IBinaryDisect::sumFaces / IBinaryDisect::cntLeafs << std::endl;
    std::cout << "Count Leafs: " << IBinaryDisect::cntLeafs << std::endl;
    std::cout << "Sum Faces: " << IBinaryDisect::sumFaces << std::endl;
    std::cout << "Größe: " << sizeof(Disect) << std::endl;

    this->box = box;
    this->disect = disect;
    std::cout << "File loaded" << std::endl;
}

void Scene::calcPixels(size_t start, size_t step, Vector3D right, Vector3D down, uint8_t* buffer, Vector3D VecToOrigin, tp starttp){
    float sceneWidthForText = box.p2.at(0) - box.p1.at(0);
    float sceneHeightForText = box.p2.at(2) - box.p1.at(2);
    float wPixelsPerWorldUint = (float)this->texture[0].getWidth() / sceneWidthForText;
    float hPixelsPerWorldUint = (float)this->texture[0].getHeight() / sceneHeightForText;

    for (size_t curH = start; curH < camera.height_pixels; curH += step)
    {
	for (size_t curW = 0; curW < camera.width_pixels; curW++)
	{
	    if(curH % 10 == 0 && curW == 0){
		proglock.lock();
		float progperc = ((float)++progress * 10 / camera.height_pixels);
		proglock.unlock();

		std::cout << ">" << (int)(progperc * 100) << "% [";
		for(int i = 0; i < 20; i++){
		    if(i < progperc * 20){
			std::cout << "#";
		    }else{
			std::cout << " ";
		    }
		}

		tp current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = (current - starttp) * (1.0 / progperc);
		auto mins = std::chrono::duration_cast<std::chrono::minutes>(duration);
		uint secs = round((duration - mins).count());
		std::cout << "] ETA: " << mins.count() << ":" << std::setfill('0') << std::setw(2) << secs << "\r" << std::flush;
	    }

	    Ray ray = Ray(camera.eye, VecToOrigin + right * (float)curW + down * (float)curH);
	    Hitpoint closest = this->disect->closestHitpoint(ray);
	    Color col;
	    if(closest.face != nullptr)
	    {
		Vector3D normale = closest.face->normal;
		Color faceCol;
		float absX = fabs(normale.getX());
		float absY = fabs(normale.getY());
		float absZ = fabs(normale.getZ());
		if(normale.getY() > fabs(normale.getZ()) && normale.getY() > fabs(normale.getX())){
		    // std::cout << normale << std::endl;
		    //Farbwert der Fläche am HP berechen
		    size_t colXpos = wPixelsPerWorldUint * (closest.position.getX() + sceneWidthForText / 2);
		    size_t colZpos = hPixelsPerWorldUint * (sceneHeightForText/2 - closest.position.getZ());
		    faceCol = texture[0].get(colXpos, colZpos);
		}else{
		    faceCol = Color(255,255,255);
		}
		for(Light l : this->lights){
		    Vector3D lightSource = l.getLightSource();
		    Vector3D path = closest.position - lightSource;
		    Vector3D lightDirection = Vector3D::normalize(path) * -1.0f;
		    Ray LightRay = Ray(lightSource, path);

		    Hitpoint LightHit = this->disect->closestHitpoint(LightRay);

		    if(LightHit.position == closest.position || closest.face == LightHit.face){
			//std::cout << " Hit" << std::endl;
			//col = closest.face->texture.color;

			float dot = Vector3D::dot(lightDirection, normale);
			float intensity = std::max(dot, 0.0f) * (1.0f / (LightHit.distance / l.fallof() + 1.0f));
			//std::cout << dot << std::endl;


			col += l.getColor().on(faceCol) * intensity; // theoretisch kommt hier noch lichtfarbe aber so ists halt 1 aka weißes licht
			//col += closest.face->texture.color * intensity;

			//col = closest.face->texture.color;s

			/*Vector3D vec  = closest.face->normal;
vec = Vector3D::normalize(vec);
col = Color(255 * vec.getX(), 255*vec.getY(), 255*vec.getZ());*/
		    }	
		}
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
    //std::cout << "Thread [" << start << "]" << std::endl;
}

void Scene::testoptimized(uint numThreads, tp start){
    std::cout << "Start Drawing" << std::endl;
    uint8_t *buffer = new uint8_t[camera.width_pixels * camera.height_pixels * 3];

    float pixelWidth = camera.width / camera.width_pixels;
    float pixelHeight = camera.height / camera.height_pixels;

    Vector3D yaxis = Vector3D(0,1,0);
    Vector3D view = Vector3D::normalize(camera.view);
    Vector3D invview = view * -1;
    std::cout << yaxis << view << invview << (yaxis == view || yaxis == invview) << std::endl;

    Vector3D right;
    if(yaxis == view || yaxis == invview){
	right = Vector3D(1,0,0);
    }else{
	right = Vector3D::cross(yaxis, view);
    }
    Vector3D down = Vector3D::cross(right, view);

    Vector3D vectorToOriginPixel = camera.view + right * (-camera.width / 2) + down * (-camera.height / 2);
    std::cout << vectorToOriginPixel << std::endl;

    down = down * (pixelHeight / down.abs());
    right = right * (pixelWidth / right.abs());

    std::vector<std::thread> threads;
    const size_t rowsPerThread = camera.height_pixels / numThreads;
    progress = 0;

    for(size_t i = 0; i < numThreads; i++){
	threads.push_back(std::thread(&Scene::calcPixels, this,i,numThreads, right, down, buffer, vectorToOriginPixel, start));
    }

    //calcPixels(disect,0,camera.height_pixels/2, pixelWidth, pixelHeight, buffer, vectorToOriginPixel);
    //calcPixels,disect,camera.height_pixels / 2 - 1,camera.height_pixels, pixelWidth, pixelHeight, buffer, vectorToOriginPixel

    for(auto& t : threads){
	t.join();
    }

    disect->dealoc();

    int success = stbi_write_png("resultate/output_opt.png", camera.width_pixels, camera.height_pixels, 3, buffer, camera.width_pixels * 3);
    delete[] buffer;

    if (!success)
    {
	std::cout << "Failed to write PNG!" << std::endl;
	return;
    }
    // 2d array von colors pro pixel zu 1D array mit rgb values 
}

/*
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
}*/

Scene::Scene(std::istream& file, int depth)
{
    this->loadFile(file, depth);
}

bool contains(BoundingBox box, Vector3D vec){
    for(uint8_t dir = 0; dir < 3; dir++){
	if(vec.at(dir) < box.p1.at(dir) || vec.at(dir) > box.p2.at(dir)){
	    return false;
	}
    }
    return true;
}

void IBinaryDisect::incrCounters(size_t size){
    IBinaryDisect::sumFaces+=size;
    if(size > IBinaryDisect::mostFaces){
	IBinaryDisect::mostFaces = size;
    }
}

void Scene::loadGraphics(std::array<std::string, 6> paths){
    this->texture[0] = Texture(paths[0]);
    /*
for(uint8_t pos = 0; pos < 6; pos++){
this->texture[pos] = Texture(paths[pos]);
}
*/
}
