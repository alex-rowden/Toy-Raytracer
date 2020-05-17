#include "MyRandom.h"

MyRandom::MyRandom(unsigned seed) {
	
	generator = std::mt19937(seed);
	uniform01 = std::uniform_real_distribution<float>(0.0, 1.0);
}

glm::vec3 MyRandom::random_in_unit_sphere()
{
	float theta = 2 * M_PI * uniform01(generator);
	float phi = acos(1 - 2 * uniform01(generator));
	return glm::vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));

}
