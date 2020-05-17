#include "BuildPPM.h"


BuildPPM::BuildPPM(std::string filename, std::vector<glm::vec3> img, int width, int height) {
	if (img.size() < width * height) {
		std::cerr << "img to small: Image is " <<img.size() << " we need " << width * height  << std::endl;
	}
	std::ofstream out(filename, std::ios::out);
	out << "P3" << std::endl;
	out << width << " " << height << std::endl;
	out << "255" << std::endl;
	glm::vec3 curr = glm::vec3();
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			curr = img.at(column + row * width);
			curr *= 255;
			out << (curr.r) << " "
				<< (curr.g) << " "
				<< (curr.b) << " ";
		}
		out << std::endl;
	}
}