#pragma once
#include "../include/Scene.hpp"
#include <limits>
#include <string>

void Scene::loadFile(std::istream* file){
	static unsigned short ignoreLines = 2;
	for(unsigned short i = 0; i < ignoreLines; i++)
		file->ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string line;
	int vertex;

	std::getline(*file,line);
	
}