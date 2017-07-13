#pragma once
#include <vector>
#include "Activation.h"

class NeuronBase
{
public:
	NeuronBase(const std::string &activation_name, int inputs_amount);
	NeuronBase(NeuronBase &n);
	virtual ~NeuronBase();
	virtual double getBiasInputWeight();
	virtual double getLastActivationValue();
	virtual double getLastActivationDerivative();
	virtual std::string getActivationName();
	virtual std::vector<double> getVecInputWeights();
	virtual double step(const std::vector<double> &inputs) = 0;
	virtual void generateWeights(double from, double to) = 0;
	virtual void updateBiasInputWeight(double weight);
	virtual void updateWeightInputIndex(double value, int index);
	void setActivationInput(std::string activation_name);
	void addWeightInput(double value);
protected:
	double bias_input_weight;
	double last_activation_value;
	double last_derivative_value;
	std::vector<double> vec_weights_input;
	Activation *activation = nullptr;
};
