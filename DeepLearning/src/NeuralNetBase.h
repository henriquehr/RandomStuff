#pragma once
#include "NeuronBase.h"
#include <vector>

class NeuralNetBase
{
public:
	NeuralNetBase();
	virtual ~NeuralNetBase();
	virtual void createNeuronsLayer(int amount, int layer, std::string activation_name, int inputs_amount) = 0;
	virtual void appendNeuronLayer(int layer, std::string activation_name, int inputs_amount) = 0;
	virtual void appendLayer(int neurons_amount, std::string activation_name, int inputs_amount) = 0;
	virtual int getNeuronsAmountLayer(int layer);
	virtual int getLayersAmount();
	virtual void setLayersAmount(int amount);
	virtual NeuronBase* getNeuronIndexLayer(int neuron_index, int layer);
	virtual void generateWeights(double from, double to);
	virtual std::vector<double>  stepLayer(std::vector<double> vec_inputs, int layer);
	std::vector<double> YesThread(std::vector<double> vec_inputs, int layer);
	std::vector<double> NoThread(std::vector<double> vec_inputs, int layer);
	void stepLayerThread(std::vector<double> *outputs, const std::vector<double>& vec_inputs, int layer, int from, int to);
	virtual std::vector<double> step(const std::vector<double> &vec_inputs);
	virtual std::vector<double> getLastNetOutput();
	virtual std::vector<double> getLastNetInput();
	virtual void updateWeightNeuronLayer(double weight, int w_index, int n_index, int l_index);
	virtual void updateBiasNeuronLayer(double weight, int n_index, int l_index);
	virtual void showNet();
	virtual void showNetWeights();
protected:
	std::vector<std::vector<NeuronBase*>> vec_layers;
	std::vector<double> vec_last_input;
	std::vector<double> vec_last_output;
};

