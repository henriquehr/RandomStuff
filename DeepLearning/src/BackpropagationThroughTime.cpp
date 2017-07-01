#include "BackpropagationThroughTime.h"

BackpropagationThroughTime::BackpropagationThroughTime() : TrainBase()
{}

BackpropagationThroughTime::~BackpropagationThroughTime()
{}

void BackpropagationThroughTime::start(NeuralNetBase * nnet, double learning_rate, const std::vector<double> &desired)
{
	//int layers_amount = lstm->getLayersAmount();
	//int hidden_layers_amount = layers_amount - 1;
	//int neurons_lastlayer_amount = lstm->getNeuronsAmountLayer(layers_amount - 1);
	//std::vector<std::vector<double>> deltas;
	//deltas.resize(layers_amount);
	//std::vector<double> vec_last_output = lstm->getLastNetOutput();
	//std::vector<double> vec_error_last;
	//vec_error_last.resize(neurons_lastlayer_amount);
	//deltas.at(layers_amount - 1).resize(neurons_lastlayer_amount);
	//// error
	//for(int j = 0; j < neurons_lastlayer_amount; j++) // output
	//{
	//	vec_error_last.at(j) = desired.at(j) - vec_last_output.at(j);
	//	deltas.at(layers_amount - 1).at(j) = lstm->getNeuronIndexLayer(j, layers_amount - 1)->getLastActivationDerivative() * vec_error_last.at(j);
	//}
	//double sum = 0.0;
	//for(int i = hidden_layers_amount; i > 0; i--) // hidden
	//{
	//	int na = lstm->getNeuronsAmountLayer(i - 1);
	//	deltas.at(i - 1).resize(na);
	//	for(int j = 0; j < na; j++)
	//	{
	//		for(int h = 0; h < lstm->getNeuronsAmountLayer(i); h++)
	//		{
	//			sum += (lstm->getNeuronIndexLayer(h, i)->getWeight(j) * deltas.at(i).at(h));
	//		}
	//		deltas.at(i - 1).at(j) = lstm->getNeuronIndexLayer(j, i - 1)->getLastActivationDerivative() * sum;
	//		sum = 0.0;
	//	}
	//}

	//// update
	//for(int i = 0; i < neurons_lastlayer_amount; i++) // output
	//{
	//	for(int j = 0; j < perc->getNeuronsAmountLayer(layers_amount - 2); j++)
	//	{
	//		perc->updateWeightNeuronLayer(learning_rate * (deltas.at(layers_amount - 1).at(i) * perc->getNeuronsLayer(layers_amount - 2).at(j)->getLastActivationValue()), j, i, layers_amount - 1);
	//	}
	//	perc->updateBiasNeuronLayer(learning_rate * deltas.at(layers_amount - 1).at(i) * -1.0, i, layers_amount - 1);
	//}

	//for(int i = hidden_layers_amount - 1; i > 0; i--) // hidden
	//{
	//	for(int j = 0; j < perc->getNeuronsAmountLayer(i); j++)
	//	{
	//		for(int h = 0; h < perc->getNeuronsAmountLayer(i - 1); h++)
	//		{
	//			perc->updateWeightNeuronLayer(learning_rate * deltas.at(i).at(j) * perc->getNeuronIndexLayer(h, i - 1)->getLastActivationValue(), h, j, i);
	//		}
	//		perc->updateBiasNeuronLayer(learning_rate * deltas.at(i).at(j) * -1.0, j, i);
	//	}
	//}

	//for(int i = 0; i < perc->getNeuronsAmountLayer(0); i++) // input
	//{
	//	for(int j = 0; j < perc->getLastNetInput().size(); j++)
	//	{
	//		perc->updateWeightNeuronLayer(learning_rate * deltas.at(0).at(i) * perc->getLastNetInput().at(j), j, i, 0);
	//	}
	//	perc->updateBiasNeuronLayer(learning_rate * deltas.at(0).at(i) * -1.0, i, 0);
	//}
}