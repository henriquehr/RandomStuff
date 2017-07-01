#pragma once
#include <string>
#include <iostream>
#include <vector>

class Image
{
public:
	Image();
	~Image();
	bool readImage(const char* filename);
	bool saveImage(const char* filename, const std::vector<unsigned char>& image, unsigned width, unsigned height);
	std::vector<std::vector<double>> getRed();
	std::vector<std::vector<double>> getGreen();
	std::vector<std::vector<double>> getBlue();
	std::vector<std::vector<double>> getAlpha();
	int getWidth();
	int getHeight();
private:
	unsigned int width;
	unsigned int height;
	std::vector<unsigned char> image;
};

