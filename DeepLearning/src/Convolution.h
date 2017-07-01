#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include "Activation.h"

class Convolution
{
public:
	Convolution();
	~Convolution();
	//std::vector<std::vector<double>> convolveKeep(const std::vector<std::vector<double>>& m);
	std::vector<std::vector<double>> convolve(const std::vector<std::vector<double>>& m, const std::vector<std::vector<double>>& filter);
	void setFilter(std::vector<std::vector<double>> filter);
	void generateFilter(int from, int to);
private:
	std::vector<std::vector<double>> filter;
	std::vector<std::vector<double>> convolved;
};

