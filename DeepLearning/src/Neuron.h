#pragma once
#include <vector>
#include "NeuronBase.h"

class Neuron :public NeuronBase
{
public:
	Neuron(const std::string &activation_name, int inputs_amount);
	~Neuron();
	double step(const std::vector<double>  &vec_inputs) override;
	void generateWeights(double from, double to) override;
private:
	double sum(const std::vector<double> &vec_inputs);
};
