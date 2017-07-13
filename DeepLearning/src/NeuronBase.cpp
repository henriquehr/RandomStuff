#include "NeuronBase.h"
#include <iostream>

NeuronBase::NeuronBase(const std::string &activation_name, int inputs_amount)
{
	this->vec_weights_input.resize(inputs_amount);
	this->last_activation_value = 0.0;
	this->last_derivative_value = 0.0;
	this->bias_input_weight = 0.0;
	this->activation = new Activation(activation_name);
}

NeuronBase::NeuronBase(NeuronBase & n)
{
	this->vec_weights_input.resize(n.getVecInputWeights().size());
	this->last_activation_value = n.last_activation_value;
	this->last_derivative_value = n.last_derivative_value;
	this->bias_input_weight = n.bias_input_weight;
	this->activation = n.activation;
}

NeuronBase::~NeuronBase()
{
	delete this->activation;
}

double NeuronBase::getBiasInputWeight()
{
	return this->bias_input_weight;
}

double NeuronBase::getLastActivationValue()
{
	return this->last_activation_value;
}

double NeuronBase::getLastActivationDerivative()
{
	return this->activation->calcDerivative(this->getActivationName(), this->last_activation_value);
}

std::string NeuronBase::getActivationName()
{
	return this->activation->getActivationName();
}

std::vector<double> NeuronBase::getVecInputWeights()
{
	return this->vec_weights_input;
}

void NeuronBase::updateBiasInputWeight(double weight)
{
	this->bias_input_weight += weight;
}

void NeuronBase::updateWeightInputIndex(double value, int index)
{
	this->vec_weights_input.at(index) += value;
}

void NeuronBase::setActivationInput(std::string activation_name)
{
	this->activation->setActivation(activation_name);
}

void NeuronBase::addWeightInput(double value)
{
	this->vec_weights_input.push_back(value);
}
