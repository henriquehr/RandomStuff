#include "Pool.h"

Pool::Pool()
{}


Pool::~Pool()
{}

std::vector<std::vector<double>> Pool::maxPool(const std::vector<std::vector<double>>& m, int pool_size)
{
	this->setSize(pool_size);
	this->pool = std::vector<std::vector<double>>();
	int shift = 2;
	int biggest = 0;
	int sizeH = m.size();
	int sizeW = m.at(0).size();
	this->pool.resize(sizeH / shift);
	int filterPosH = 0;
	int filterPosW = 0;
	for (int i = 0; i < sizeH; i += shift)
	{
		this->pool.at(filterPosH).resize(sizeW / shift);
		for (int j = 0; j < sizeW; j += shift)
		{
			for (int h = 0; h < this->poolSize; h++)
			{
				for (int p = 0; p < this->poolSize; p++)
				{
					if ((i + h) < sizeH && (j + p) < sizeW) {
						double t = m.at(i + h).at(j + p);
						t > biggest ? biggest = t : biggest = biggest;
					}
				}
			}
			this->pool.at(filterPosH).at(filterPosW) = biggest;
			filterPosW++;
		}
		filterPosW = 0;
		filterPosH++;
	}
	return this->pool;
}

std::vector<std::vector<double>> Pool::meanPool(const std::vector<std::vector<double>>& m, int pool_size)
{
	this->setSize(pool_size);
	this->pool = std::vector<std::vector<double>>();
	int shift = 2;
	int mean = 0;
	int sizeH = m.size();
	int sizeW = m.at(0).size();
	if (sizeH % 2 != 0) {
		sizeH--;
	}if (sizeW % 2 != 0) {
		sizeW--;
	}
	this->pool.resize(sizeH/ shift);
	int filterPosH = 0;
	int filterPosW = 0;
	for (int i = 0; i < sizeH; i+= shift)
	{
		this->pool.at(filterPosH).resize(sizeW / shift);
		for (int j = 0; j < sizeW; j+= shift)
		{
			for (int h = 0; h < this->poolSize; h++)
			{
				for (int p = 0; p < this->poolSize; p++)
				{
					if ((i + h) < sizeH && (j + p) < sizeW) {
						mean += m.at(i + h).at(j + p);
					}
					else {
						mean += m.at(i).at(j);
					}
				}
			}
			this->pool.at(filterPosH).at(filterPosW) = mean / (this->poolSize * this->poolSize);
			mean = 0;
			filterPosW++;
		}
		filterPosW = 0;
		filterPosH++;
	}
	return this->pool;
}

void Pool::setSize(int size)
{
	this->poolSize = size;
}
