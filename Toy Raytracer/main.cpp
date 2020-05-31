#include "BuildPPM.h"
#include "Ray.h"
#include "ObjectList.h"
#include "Sphere.h"
#include <random>
#include <chrono>
#include "MyRandom.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Camera.h"

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
			return attenuation * getColor(scattered, scene, depth+1);
		}
		else {
			return glm::vec3(0, 0, 0);
		}
	}
	float t = r.getDirection().y * .5f + .5f;
	return glm::vec3((1 - t)) + t * glm::vec3(0.5, 0.7, 1.0);
}

Object* makeRandomScene() {
	int n = 500;
	Object** list = new Object * [n + 1];
	list[0] = new Sphere(glm::vec3(0, -1000, 0), 1000, new Lambertian(glm::vec3(.5, .5, .5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = rand() / (float)RAND_MAX;
			glm::vec3 center(a + .9 * rand() / (float)RAND_MAX, .2, b + .9 * rand() / (float)RAND_MAX);
			if (glm::length(center - glm::vec3(4, .2, 0)) > .9) {
				if (choose_mat < .8) {
					list[i++] = new Sphere(center, .2, new Lambertian(glm::vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)));
				}
				else if (choose_mat < .95) {
					list[i++] = new Sphere(center, .2, new Metal(glm::vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)));
				}
				else {
					list[i++] = new Sphere(center, .2, new Dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(glm::vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(glm::vec3(-4, 1, 0), 1.0, new Lambertian(glm::vec3(.4, .2, .1)));
	list[i++] = new Sphere(glm::vec3(4, 1, 0), 1.0, new Metal(glm::vec3(.7, .6, .5)));
	return new ObjectList(list, i);
}


int main() {
	//setup random number machine...
	MyRandom random = MyRandom(std::chrono::system_clock::now().time_since_epoch().count());

	std::vector<glm::vec3> img = std::vector<glm::vec3>();
	int nx = 1080;
	int ny = 720;
	int num_samples = 100;
	glm::vec3 curr = glm::vec3();
	float R = cos(M_PI / 4.0f);
	//Object* list[5];
	//list[0] = new Sphere(glm::vec3(0, 0, -1), .5, new Lambertian(glm::vec3(.1, .2, .5)));
	//list[1] = new Sphere(glm::vec3(0, -100.5, -1), 100, new Lambertian(glm::vec3(.8, .8, 0)));
	//list[2] = new Sphere(glm::vec3(1, 0, -1), .5, new Metal(glm::vec3(.8, .6, .2)));
	//list[3] = new Sphere(glm::vec3(-1, 0, -1), .5, new Dielectric(1.5));
	//list[4] = new Sphere(glm::vec3(-1, 0, -1), -.45, new Dielectric(1.5));
	
	glm::vec3 lookfrom(4, 1, 0);
	glm::vec3 lookat(0, 0, -1);
	float dist_to_focus = glm::length(lookfrom - lookat);
	Object* scene = makeRandomScene();
	Camera camera(lookfrom, lookat, glm::vec3(0, 1, 0), 90, nx / (float)ny, 0, 1);
	//list[4] = new Sphere(glm::vec3(-1, 0, -1), -.45, new Dielectric(1.5f));
	//Object* scene = new ObjectList(list, 5);
	img.resize(nx * ny);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			glm::vec3 color = glm::vec3();
			for (int sample = 0; sample < num_samples; sample++) {
				
				Ray r = camera.getRay(u + rand()/(RAND_MAX * nx), v + rand()/(RAND_MAX * ny));

				 color += getColor(r, scene, 0);
			}
			color = color / (float)num_samples;
			img.at(i + (ny - j - 1) * nx) = glm::vec3(sqrt(color.r), sqrt(color.g), sqrt(color.b));
		}
	}
	BuildPPM("test", img, nx, ny);
}