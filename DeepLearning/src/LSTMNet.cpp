#include "LSTMNet.h"
#include <iostream>
#include "LSTMCell.h"

LSTMNet::LSTMNet() :NeuralNetBase()
{}

LSTMNet::~LSTMNet()
{}

void LSTMNet::createNeuronsLayer(int amount, int layer, std::string activation_name, int inputs_amount)
{
	vec_layers.at(layer).resize(amount);
	for(int i = 0; i < amount; i++)
	{
		this->vec_layers.at(layer).at(i) = new LSTMCell(activation_name, inputs_amount);
	}
}

void LSTMNet::appendNeuronLayer(int layer, std::string activation_name, int inputs_amount)
{
	this->vec_layers.at(layer).push_back(new LSTMCell(activation_name, inputs_amount));
}

void LSTMNet::appendLayer(int neurons_amount, std::string activation_name, int inputs_amount)
{
	this->vec_layers.push_back(std::vector<NeuronBase*>());
	for(int i = 0; i < neurons_amount; i++)
	{
		this->vec_layers.at(this->vec_layers.size() - 1).push_back(new LSTMCell(activation_name, inputs_amount));
	}
}