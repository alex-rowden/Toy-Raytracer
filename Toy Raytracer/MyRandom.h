#pragma once
#include <glm.hpp>
#include <random>
#include <chrono>

#define M_PI 3.1415926535897932384626433

class MyRandom
{
public:
	std::mt19937 generator;
	std::uniform_real_distribution<float> uniform01;
	MyRandom(unsigned seed);
	glm::vec3 random_in_unit_sphere();
};

