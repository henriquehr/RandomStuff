#pragma once
#include <string>
#include <vector>
#include "NeuronBase.h"

class RecurrentNeuron : public NeuronBase
{
public:
	RecurrentNeuron(const std::string &activation_name, int inputs_amount);
	~RecurrentNeuron(); 
	double step(const std::vector<double>  &vec_inputs) override;
	void generateWeights(double from, double to) override;
private:
	double sum(const std::vector<double> &vec_inputs);
};

