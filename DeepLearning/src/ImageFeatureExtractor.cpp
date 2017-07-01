#include "ImageFeatureExtractor.h"
#include <thread>

ImageFeatureExtractor::ImageFeatureExtractor()
{}


ImageFeatureExtractor::~ImageFeatureExtractor()
{}

std::vector<std::vector<std::vector<double>>> ImageFeatureExtractor::loadImage(char* file_name) {
	Image i;
	printf("Loading image...");
	if (!i.readImage(file_name)) {
		this->lastResult = std::vector<std::vector<std::vector<double>>>(3);
		this->lastResult.at(0) = i.getRed();
		this->lastResult.at(1) = i.getGreen();
		this->lastResult.at(2) = i.getBlue();
		printf("Done\n");
		return this->lastResult;
	}
	else {
		printf("Couldn't load the Image %s\n", file_name);
		this->lastResult = std::vector<std::vector<std::vector<double>>>(3);
		return this->lastResult;
	}
}

bool ImageFeatureExtractor::saveImage(const std::vector<std::vector<std::vector<double>>>& image, char* file_name) {
	printf("Saving image...");
	int sizeH = image.at(0).size();
	int sizeW = image.at(0).at(0).size();
	std::vector<unsigned char> toSave(sizeH * sizeW * 4);
	int saveIdx = 0;
	for (int i = 0; i < sizeH; i++)
	{
		for (int j = 0; j < sizeW; j++)
		{
			toSave.at(saveIdx) = image.at(0).at(i).at(j);
			saveIdx++;
			toSave.at(saveIdx) = image.at(1).at(i).at(j);
			saveIdx++;
			toSave.at(saveIdx) = image.at(2).at(i).at(j);
			saveIdx++;
			toSave.at(saveIdx) = 255;
			saveIdx++;
		}
	}
	Image i;
	if (!i.saveImage(file_name, toSave, sizeH, sizeW)) {
		printf("Image saved\n");
		return true;
	}
	else {
		printf("Image couldn't be saved\n");
		return false;
	}
}

std::vector<std::vector<std::vector<double>>> ImageFeatureExtractor::convolve(const std::vector<std::vector<std::vector<double>>>& image, int filter) {
	printf("Convolving...");
	//Convolution c;
	//this->lastResult = std::vector<std::vector<std::vector<double>>>(3);
	std::vector<std::vector<std::vector<double>>> temp(3);
	std::thread th1, th2, th3;
	th1 = std::thread([&temp, &image, &filter]() {Convolution c; temp.at(0) = c.convolve(image.at(0), filter); });
	th2 = std::thread([&temp, &image, &filter]() {Convolution c; temp.at(1) = c.convolve(image.at(1), filter); });
	th3 = std::thread([&temp, &image, &filter]() {Convolution c; temp.at(2) = c.convolve(image.at(2), filter); });
	//this->lastResult.at(0) = c.convolve(image.at(0), filter);
	//this->lastResult.at(1) = c.convolve(image.at(1), filter);
	//this->lastResult.at(2) = c.convolve(image.at(2), filter);
	th1.join();
	th2.join();
	th3.join();
	this->lastResult = temp;
	printf("Done\n");
	return this->lastResult;
}

std::vector<std::vector<std::vector<double>>> ImageFeatureExtractor::pool(const std::vector<std::vector<std::vector<double>>>& image, int pool_size) {
	printf("Pooling...");
	//Pool p;
	//this->lastResult = std::vector<std::vector<std::vector<double>>>(3);
	std::vector<std::vector<std::vector<double>>> temp(3);
	std::thread th1, th2, th3;
	th1 = std::thread([&temp, &image, &pool_size]() {Pool p; temp.at(0) = p.meanPool(image.at(0), pool_size); });
	th2 = std::thread([&temp, &image, &pool_size]() {Pool p; temp.at(1) = p.meanPool(image.at(1), pool_size); });
	th3 = std::thread([&temp, &image, &pool_size]() {Pool p; temp.at(2) = p.meanPool(image.at(2), pool_size); });
	//this->lastResult.at(0) = p.meanPool(image.at(0), pool_size);
	//this->lastResult.at(1) = p.meanPool(image.at(1), pool_size);
	//this->lastResult.at(2) = p.meanPool(image.at(2), pool_size);
	th1.join();
	th2.join();
	th3.join();
	this->lastResult = temp;
	printf("Done\n");
	return this->lastResult;
}