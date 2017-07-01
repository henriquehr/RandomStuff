#pragma once
#include "NeuralNetBase.h"

class LSTMNet :public NeuralNetBase
{
public:
	LSTMNet();
	~LSTMNet();
	void createNeuronsLayer(int amount, int layer, std::string activation_name, int inputs_amount) override;
	void appendNeuronLayer(int layer, std::string activation_name, int inputs_amount) override;
	void appendLayer(int neurons_amount, std::string activation_name, int inputs_amount) override;
};
