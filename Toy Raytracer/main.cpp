#include "BuildPPM.h"
#include "Ray.h"
#include "ObjectList.h"
#include "Sphere.h"
#include <random>
#include <chrono>
#include "MyRandom.h"
#include "Lambertian.h"

#define M_PI 3.1415926535897932384626433
#define EPSILON 1e-3


float hit_sphere(glm::vec3 center, float radius, Ray& r) {
	glm::vec3 origin_center = r.getOrigin() - center;
	float ray_length = glm::dot(r.getDirection(), r.getDirection());
	float b = 2.0 * dot(origin_center, r.getDirection());
	float c = dot(origin_center, origin_center) - radius * radius;
	float discriminant = b * b - 4 * ray_length * c;
	if (discriminant < 0)
		return -1;
	else {
		return (-b - sqrt(discriminant)) / (2 * ray_length);
	}
}


glm::vec3 getColor(Ray& r, Object *scene, int depth) {
	hit_record rec;
	if (scene->hit(r, EPSILON, std::numeric_limits<float>().max(), rec)) {
		Ray scattered;
		glm::vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * getColor(scattered, scene, depth++);
		}
	}
	float t = r.getDirection().y * .5f + .5f;
	return glm::vec3((1 - t)) + t * glm::vec3(0.5, 0.7, 1.0);
}


int main() {
	//setup random number machine...
	MyRandom random = MyRandom(std::chrono::system_clock::now().time_since_epoch().count());

	std::vector<glm::vec3> img = std::vector<glm::vec3>();
	int nx = 200;
	int ny = 100;
	int num_samples = 100;
	glm::vec3 curr = glm::vec3();
	glm::vec3 lower_left_corner(-2, -1, -1);
	glm::vec3 horizontal(4, 0, 0);
	glm::vec3 vertical(0, 2, 0);
	glm::vec3 origin(0, 0, 0);
	Object* list[2];
	list[0] = new Sphere(glm::vec3(0, 0, -1), .5, new Lambertian(glm::vec3(0,0,1), random));
	list[1] = new Sphere(glm::vec3(0, -100.5, -1), 100, new Lambertian(glm::vec3(0,1,0), random));
	Object* scene = new ObjectList(list, 2);
	img.resize(nx * ny);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			glm::vec3 color = glm::vec3();
			for (int sample = 0; sample < num_samples; sample++) {
				
				Ray r(origin, lower_left_corner + ((u + random.uniform01(random.generator)/(float)(nx)) * horizontal + (v + random.uniform01(random.generator)/(float)(ny)) * vertical));

				 color += getColor(r, scene, 0);
			}
			color = color / (float)num_samples;
			img.at(i + (ny - j - 1) * nx) = glm::vec3(sqrt(color.r), sqrt(color.g), sqrt(color.b));
		}
	}
	BuildPPM("test", img, nx, ny);
}