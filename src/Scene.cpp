#include "../include/Scene.hpp"
#include <cstddef>
#include <exception>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

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

Scene::Scene(){	
}