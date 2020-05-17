#pragma once
#include <string>
#include<vector>
#include <glm.hpp>
#include <iostream>
#include <fstream>
class BuildPPM
{
public:
	/*
	filname	~	string representing the name of the file - w/o .ppm
	img		~	flattened image stored in a vector row major order
	width	~	number of columns
	height	~	number of rows
	*/
	BuildPPM(std::string filename, std::vector<glm::vec3> img, int width, int height);
};

