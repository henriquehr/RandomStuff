#include "Image.h"
#include "lodepng.cpp"

Image::Image()
{}

Image::~Image()
{
	//std::vector<unsigned char>().swap(this->image);
}

bool Image::readImage(const char* filename)
{
	unsigned width, height;
	bool r = false;

	//decode
	unsigned error = lodepng::decode(this->image, width, height, filename);
	this->width = width;
	this->height = height;
	//if there's an error, display it
	if (error) {
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		r = true;
	}

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

	return r;
}

bool Image::saveImage(const char* filename, const std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	bool r = false;
	unsigned error = lodepng::encode(filename, image, width, height);

	if (error) {
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		r = true;
	}
	return r;
}


std::vector<std::vector<double>> Image::getRed() {
	std::vector<std::vector<double>> channel;
	channel.resize(this->width);
	int v = 0;
	for (int i = 0; i < this->width; i++)
	{
		channel.at(i).resize(this->height);
		for (int j = 0; j < this->height; j++)
		{
			channel.at(i).at(j) = image.at(v);
			v += 4;
		}
	}
	return channel;
}

std::vector<std::vector<double>> Image::getGreen() {
	std::vector<std::vector<double>> channel;
	channel.resize(this->width);
	int v = 1;
	for (int i = 0; i < this->width; i++)
	{
		channel.at(i).resize(this->height);
		for (int j = 0; j < this->height; j++)
		{
			channel.at(i).at(j) = image.at(v);
			v += 4;
		}
	}
	return channel;
}

std::vector<std::vector<double>> Image::getBlue() {
	std::vector<std::vector<double>> channel;
	channel.resize(this->width);
	int v = 2;
	for (int i = 0; i < this->width; i++)
	{
		channel.at(i).resize(this->height);
		for (int j = 0; j < this->height; j++)
		{
			channel.at(i).at(j) = image.at(v);
			v += 4;
		}
	}
	return channel;
}

std::vector<std::vector<double>> Image::getAlpha() {
	std::vector<std::vector<double>> channel;
	channel.resize(this->width);
	int v = 3;
	for (int i = 0; i < this->width; i++)
	{
		channel.at(i).resize(this->height);
		for (int j = 0; j < this->height; j++)
		{
			channel.at(i).at(j) = image.at(v);
			v += 4;
		}
	}
	return channel;
}



int Image::getHeight() {
	return (int)this->height;
}

int Image::getWidth() {
	return (int)this->width;
}


