#pragma once
#include "Image.h"
#include "Convolution.h"
#include "Pool.h"

class ImageFeatureExtractor
{
public:
	ImageFeatureExtractor();
	~ImageFeatureExtractor();
	std::vector<std::vector<std::vector<double>>> loadImage(char* file_name);
	bool saveImage(const std::vector<std::vector<std::vector<double>>>& image, char* file_name);
	std::vector<std::vector<std::vector<double>>> convolve(const std::vector<std::vector<std::vector<double>>>& image, int filter);
	std::vector<std::vector<std::vector<double>>> pool(const std::vector<std::vector<std::vector<double>>>& image, int pool_size);
private:
	std::vector<std::vector<std::vector<double>>> lastResult;
};

