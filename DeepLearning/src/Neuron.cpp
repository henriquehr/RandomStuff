#include "Neuron.h"
#include <random>

Neuron::Neuron(const std::string &activation_name, int inputs_amount) :NeuronBase(activation_name, inputs_amount) {}

Neuron::~Neuron() {}

double Neuron::step(const std::vector<double>  &vec_inputs)
{
	double last_sum = this->sum(vec_inputs);
	double actv = this->activation->calcActivation(this->getActivationName(), last_sum);
	this->last_activation_value = actv;
	return actv;
}

void Neuron::generateWeights(double from, double to)
{
	std::random_device rseed;
	std::mt19937 rgen(rseed());
	std::uniform_real_distribution<double> urd(from, to);
	int s = this->getVecInputWeights().size();
	for(int i = 0; i < s; i++)
	{
		vec_weights_input.at(i) = urd(rgen);
	}
	this->bias_input_weight = urd(rgen);
}

double Neuron::sum(const std::vector<double> &vec_inputs)
{
	double sum = 0.0;
	int s = vec_inputs.size();
	for(int i = 0; i < s; i++)
	{
		sum += this->vec_weights_input.at(i) * vec_inputs.at(i);
	}
	sum += this->bias_input_weight * -1;
	return sum;
}