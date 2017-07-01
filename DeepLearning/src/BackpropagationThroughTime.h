#pragma once
#include <vector>
#include "TrainBase.h"

class BackpropagationThroughTime: public TrainBase
{
public:
	BackpropagationThroughTime();
	~BackpropagationThroughTime();
	virtual void start(NeuralNetBase* nnet, double learning_rate, const std::vector<double> &desired) override;
};
