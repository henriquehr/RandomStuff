#pragma once
#include <vector>
#include "NeuronBase.h"

class LSTMCell :public NeuronBase
{
public:
	LSTMCell(const std::string &activation_name, int inputs_amount);
	~LSTMCell();
	std::vector<double> getVecIGateWeights();
	std::vector<double> getVecOGateWeights();
	std::vector<double> getVecFGateWeights();
	double step(const std::vector<double>  &vec_inputs) override;
	void generateWeights(double from, double to) override;
	void setActivation(std::string activation_name);
	double getBiasIGateWeight();
	double getBiasOGateWeight();
	double getBiasFGateWeight();
	void updateBiasIGateWeight(double weight);
	void updateBiasOGateWeight(double weight);
	void updateBiasFGateWeight(double weight);
	void updateWeightIGateIndex(double value, int index);
	void updateWeightOGateIndex(double value, int index);
	void updateWeightFGateIndex(double value, int index);
private:
	std::vector<double> vec_weights_I_gate;
	std::vector<double> vec_weights_O_gate;
	std::vector<double> vec_weights_F_gate;
	double bias_I_gate_weight = 0.0;
	double bias_O_gate_weight = 0.0;
	double bias_F_gate_weight = 0.0;
	double last_cell_value = 0.0;
	std::string activation_name_gates = "Sigmoid";
	std::vector<double> vec_last_inputs;
	int inputs_amount_total = 0;
};
