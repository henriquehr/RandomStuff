#pragma once
#include "NeuralNetBase.h"

class PerceptronNet :public NeuralNetBase
{
public:
	PerceptronNet();
	~PerceptronNet();
	void createNeuronsLayer(int amount, int layer, std::string activation_name, int inputs_amount) override;
	void appendNeuronLayer(int layer, std::string activation_name, int inputs_amount) override;
	void appendLayer(int neurons_amount, std::string activation_name, int inputs_amount) override;
};
