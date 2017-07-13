#include "NeuralNetBase.h"
#include "Neuron.h"
#include <iostream>
#include <thread>
#include "Benchmark.h"


NeuralNetBase::NeuralNetBase()
{}

NeuralNetBase::~NeuralNetBase()
{
	int s = this->vec_layers.size();
	for (int i = 0; i < s; i++)
	{
		int ss = this->vec_layers.at(i).size();
		for (int j = 0; j < ss; j++)
		{
			delete vec_layers.at(i).at(j);
		}
	}
}

int NeuralNetBase::getNeuronsAmountLayer(int layer)
{
	return this->vec_layers.at(layer).size();;
}

int NeuralNetBase::getLayersAmount()
{
	return this->vec_layers.size();;
}

void NeuralNetBase::setLayersAmount(int amount)
{
	this->vec_layers.resize(amount);
}

NeuronBase * NeuralNetBase::getNeuronIndexLayer(int neuron_index, int layer)
{
	return this->vec_layers.at(layer).at(neuron_index);
}

void NeuralNetBase::generateWeights(double from, double to)
{
	Benchmark b;
	printf("generateWeights()...");
	b.start();
	std::thread th1, th2;
	int s = this->vec_layers.size();
	int s2 = s / 2;
	th1 = std::thread([this, from, to, s2] {
		for (int i = 0; i < s2; i++)
		{
			std::thread thIn3, thIn4;
			int ss = this->vec_layers.at(i).size();
			int ss2 = ss / 2;
			thIn3 = std::thread([this, ss, i, from, to, ss2] {
				for (int j = 0; j < ss2; j++)
				{
					this->vec_layers.at(i).at(j)->generateWeights(from, to);
				}
			});
			thIn4 = std::thread([this, ss, i, from, to, ss2] {
				for (int j = ss2; j < ss; j++)
				{
					this->vec_layers.at(i).at(j)->generateWeights(from, to);
				}
			});
			thIn3.join();
			thIn4.join();
		}
	});
	th2 = std::thread([this, from, to, s2, s] {
		for (int i = s2; i < s; i++)
		{
			std::thread thIn3, thIn4;
			int ss = this->vec_layers.at(i).size();
			int ss2 = ss / 2;
			thIn3 = std::thread([this, ss, i, from, to, ss2] {
				for (int j = 0; j < ss2; j++)
				{
					this->vec_layers.at(i).at(j)->generateWeights(from, to);
				}
			});
			thIn4 = std::thread([this, ss, i, from, to, ss2] {
				for (int j = ss2; j < ss; j++)
				{
					this->vec_layers.at(i).at(j)->generateWeights(from, to);
				}
			});
			thIn3.join();
			thIn4.join();
		}
	});
	th1.join();
	th2.join();
	b.stop();
	printf("Done:");
	b.show(" ");
}

std::vector<double> NeuralNetBase::stepLayer(std::vector<double> vec_inputs, int layer)
{
	return this->YesThread(vec_inputs, layer);
	//return this->NoThread(vec_inputs, layer);
}
std::vector<double> NeuralNetBase::YesThread(std::vector<double> vec_inputs, int layer)
{
	std::vector<double> outputs;
	int s = vec_layers.at(layer).size();
	outputs.resize(s);
	std::thread th, th1, th2, th3, th4, th5, th6, th7;
	int from = 0;
	int to = s;
	th = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, from, (to / 8)); });
	th1 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8), (to / 8) * 2); });
	th2 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 2, (to / 8) * 3); });
	th3 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 3, (to / 8) * 4); });
	th4 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 4, (to / 8) * 5); });
	th5 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 5, (to / 8) * 6); });
	th6 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 6, (to / 8) * 7); });
	th7 = std::thread([this, &outputs, vec_inputs, layer, from, to] { this->stepLayerThread(&outputs, vec_inputs, layer, (to / 8) * 7, to); });
	th.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
	return outputs;
}
std::vector<double> NeuralNetBase::NoThread(std::vector<double> vec_inputs, int layer)
{
	std::vector<double> outputs;
	int s = vec_layers.at(layer).size();
	outputs.resize(s);
	std::thread th, th1, th2, th3;
	int from = 0;
	int to = s;
	this->stepLayerThread(&outputs, vec_inputs, layer, from, to);
	return outputs;
}
void NeuralNetBase::stepLayerThread(std::vector<double> *outputs, const std::vector<double> &vec_inputs, int layer, int from, int to)
{
	for (int j = from; j < to; j++)
	{
		outputs->at(j) = vec_layers.at(layer).at(j)->step(vec_inputs);
	}
}

std::vector<double> NeuralNetBase::step(const std::vector<double>& vec_inputs)
{
	Benchmark b;
	printf("Forward step started...");
	printf("Number of Inputs: %d...", vec_inputs.size());
	b.start();
	this->vec_last_input = vec_inputs;
	std::vector<std::vector<double>> outputs;
	int s = vec_layers.size();
	outputs.resize(s + 1);
	outputs.at(0) = vec_inputs;
	for (int i = 0; i < s; i++)
	{
		outputs.at(i + 1) = this->stepLayer(outputs.at(i), i);
	}
	this->vec_last_output = outputs.at(outputs.size() - 1);
	b.stop();
	printf("Forward step done...");
	b.show(" ");
	return this->vec_last_output;
}

std::vector<double> NeuralNetBase::getLastNetOutput()
{
	return this->vec_last_output;
}

std::vector<double> NeuralNetBase::getLastNetInput()
{
	return this->vec_last_input;
}

void NeuralNetBase::updateWeightNeuronLayer(double weight, int w_index, int n_index, int l_index)
{
	this->vec_layers.at(l_index).at(n_index)->updateWeightInputIndex(weight, w_index);
}

void NeuralNetBase::updateBiasNeuronLayer(double weight, int n_index, int l_index)
{
	this->vec_layers.at(l_index).at(n_index)->updateBiasInputWeight(weight);
}

void NeuralNetBase::showNet()
{
	int s = this->vec_layers.size();
	for (int i = 0; i < s; i++)
	{
		std::cout << "Layer: " << i << std::endl;
		int ss = this->vec_layers.at(i).size();
		for (int j = 0; j < ss; j++)
		{
			std::cout << this->vec_layers.at(i).at(j)->getLastActivationValue() << " - ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void NeuralNetBase::showNetWeights()
{
	int s = this->vec_layers.size();
	for (int i = 0; i < s; i++)
	{
		std::cout << "Layer: " << i << std::endl;
		int ss = this->vec_layers.at(i).size();
		for (int j = 0; j < ss; j++)
		{
			std::cout << "Neuron: " << j;
			std::cout << " >> Bias: " << this->vec_layers.at(i).at(j)->getBiasInputWeight() << std::endl;
			int sss = this->vec_layers.at(i).at(j)->getVecInputWeights().size();
			for (int h = 0; h < sss; h++)
			{
				std::cout << this->vec_layers.at(i).at(j)->getVecInputWeights().at(h) << " | ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
