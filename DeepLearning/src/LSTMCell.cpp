#include "LSTMCell.h"
#include <random>

LSTMCell::LSTMCell(const std::string &activation_name, int inputs_amount) : NeuronBase(activation_name, inputs_amount + 1)
{
	this->inputs_amount_total = inputs_amount + 1;
	this->vec_last_inputs.resize(inputs_amount);
	this->vec_weights_I_gate.resize(this->inputs_amount_total);
	this->vec_weights_O_gate.resize(this->inputs_amount_total);
	this->vec_weights_F_gate.resize(this->inputs_amount_total);
}

LSTMCell::~LSTMCell()
{}

std::vector<double> LSTMCell::getVecIGateWeights()
{
	return this->vec_weights_I_gate;
}

std::vector<double> LSTMCell::getVecOGateWeights()
{
	return this->vec_weights_O_gate;
}

std::vector<double> LSTMCell::getVecFGateWeights()
{
	return this->vec_weights_F_gate;
}

void LSTMCell::setActivation(std::string activation_name)
{
	this->activation->setActivation(activation_name);
}

void LSTMCell::generateWeights(double from, double to)
{
	std::random_device rseed;
	std::mt19937 rgen(rseed());
	std::uniform_real_distribution<double> urd(from, to);
	int s = this->vec_weights_input.size();
	for(int i = 0; i < s; i++)
	{
		this->vec_weights_input.at(i) = urd(rgen);
		this->vec_weights_I_gate.at(i) = urd(rgen);
		this->vec_weights_O_gate.at(i) = urd(rgen);
		this->vec_weights_F_gate.at(i) = urd(rgen);
	}
	this->bias_input_weight = urd(rgen);
	this->bias_I_gate_weight = urd(rgen);
	this->bias_O_gate_weight = urd(rgen);
	this->bias_F_gate_weight = urd(rgen);
}

double LSTMCell::getBiasIGateWeight()
{
	return this->bias_I_gate_weight;
}

double LSTMCell::getBiasOGateWeight()
{
	return this->bias_O_gate_weight;
}

double LSTMCell::getBiasFGateWeight()
{
	return this->bias_F_gate_weight;
}

void LSTMCell::updateBiasIGateWeight(double weight)
{
	this->bias_I_gate_weight += weight;
}

void LSTMCell::updateBiasOGateWeight(double weight)
{
	this->bias_O_gate_weight += weight;
}

void LSTMCell::updateBiasFGateWeight(double weight)
{
	this->bias_F_gate_weight += weight;
}

void LSTMCell::updateWeightIGateIndex(double value, int index)
{
	this->vec_weights_I_gate.at(index) += value;
}

void LSTMCell::updateWeightOGateIndex(double value, int index)
{
	this->vec_weights_O_gate.at(index) += value;
}

void LSTMCell::updateWeightFGateIndex(double value, int index)
{
	this->vec_weights_F_gate.at(index) += value;
}

double LSTMCell::step(const std::vector<double> &vec_inputs)
{
	double sum_input = 0.0;
	double sum_I_gate = 0.0;
	double sum_O_gate = 0.0;
	double sum_F_gate = 0.0;
	int s = vec_inputs.size();
	for(int i = 0; i < s; i++)
	{
		sum_input += this->vec_weights_input.at(i) * vec_inputs.at(i);
		sum_I_gate += this->vec_weights_I_gate.at(i) * vec_inputs.at(i);
		sum_O_gate += this->vec_weights_O_gate.at(i) * vec_inputs.at(i);
		sum_F_gate += this->vec_weights_F_gate.at(i) * vec_inputs.at(i);
	}
	sum_input += this->vec_weights_input.at(vec_weights_input.size() - 1) * this->last_activation_value;
	sum_I_gate += this->vec_weights_I_gate.at(vec_weights_I_gate.size() - 1) * this->last_activation_value;
	sum_O_gate += this->vec_weights_O_gate.at(vec_weights_O_gate.size() - 1) * this->last_activation_value;
	sum_F_gate += this->vec_weights_F_gate.at(vec_weights_F_gate.size() - 1) * this->last_activation_value;
	sum_input += this->bias_input_weight * -1;
	sum_I_gate += this->bias_I_gate_weight * -1;
	sum_O_gate += this->bias_O_gate_weight * -1;
	sum_F_gate += this->bias_F_gate_weight * -1;
	double act_input = activation->calcActivation(this->getActivationName(),sum_input);
	double act_I_gate = activation->calcActivation(this->activation_name_gates, sum_I_gate);
	double act_O_gate = activation->calcActivation(this->activation_name_gates, sum_O_gate);
	double act_F_gate = activation->calcActivation(this->activation_name_gates, sum_F_gate);
	double mult_inp_igate = act_input * act_I_gate;
	double mult_cell_fgate = this->last_cell_value * act_F_gate;
	this->last_cell_value = mult_inp_igate + mult_cell_fgate;
	double act_out = activation->calcActivation(this->getActivationName(), this->last_cell_value);
	double mult_out_ogate = act_out * act_O_gate;
	this->last_activation_value = mult_out_ogate;
	this->vec_last_inputs = vec_inputs;
	return mult_out_ogate;
}