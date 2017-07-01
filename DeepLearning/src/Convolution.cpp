#include "Convolution.h"


Convolution::Convolution()
{}


Convolution::~Convolution()
{
	//std::vector<std::vector<double>>().swap(filter);
	//std::vector<std::vector<double>>().swap(convolved);
}


std::vector<std::vector<double>> Convolution::convolve(const std::vector<std::vector<double>>& m, const std::vector<std::vector<double>>& filter) {
	Activation a("ReLU");
	this->setFilter(filter);
	this->convolved = std::vector<std::vector<double>>();
	int imgH = m.size();
	int filH = this->filter.size();
	int filW = this->filter.at(0).size();
	int imgW = m.at(0).size();
	int newSizeH = imgH - 2;
	int newSizeW = imgW - 2;
	this->convolved.resize(newSizeH);
	for (int i = 0; i < newSizeH; i++) //image
	{
		this->convolved.at(i).resize(newSizeW);
		for (int h = 0; h < newSizeW; h++) //image
		{
			for (int j = 0; j < filH; j++) //filter
			{
				for (int p = 0; p < filW; p++) //filter
				{
					this->convolved.at(i).at(h) += m.at(i + j).at(h + p) * this->filter.at(j).at(p);
				}
			}

			this->convolved.at(i).at(h) = a.calcActivation("ReLU", this->convolved.at(i).at(h));
		}
	}
	return this->convolved;
}

void Convolution::generateFilter(int from, int to)
{
	int sizeH = this->filter.size();
	int sizeW = this->filter.at(0).size();
	std::random_device rseed;
	std::mt19937 rgen(rseed());
	std::uniform_real_distribution<double> urd(from, to);
	for (int i = 0; i < sizeH; i++)
	{
		for (int j = 0; j < sizeW; j++)
		{
			this->filter.at(i).at(j) = urd(rgen);
		}
	}
}

void Convolution::setFilter(std::vector<std::vector<double>> filter)
{
	this->filter = filter;
}
