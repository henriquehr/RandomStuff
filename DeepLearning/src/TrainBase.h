#pragma once
#include <vector>
#include "NeuralNetBase.h"

class TrainBase
{
public:
	TrainBase();
	virtual ~TrainBase();
	virtual void start(NeuralNetBase* nnet, double learning_rate, const std::vector<double>& desired) = 0;
protected:
	double learning_rate = 0.1;
};

