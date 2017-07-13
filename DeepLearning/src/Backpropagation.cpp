#include "Backpropagation.h"
#include <thread>
#include <ostream>
#include <iostream>
#include "Benchmark.h"

Backpropagation::Backpropagation() :TrainBase() {}

Backpropagation::~Backpropagation() {}

void Backpropagation::start(NeuralNetBase *nnet, double learning_rate, const std::vector<double> &desired)
{
	Benchmark b;
	printf("Backward step started...");
	b.start();
	YesThread(nnet, learning_rate, desired);
	//NoThread(nnet, learning_rate, desired);
	b.stop();
	printf("Backward step done...");
	b.show(" ");
}

void Backpropagation::YesThread(NeuralNetBase *nnet, double learning_rate, const std::vector<double> &desired)
{
	printf("Calculating errors...\n");
	Benchmark b;
	this->learning_rate = learning_rate;
	int layers_amount = nnet->getLayersAmount();
	int hidden_layers_amount = layers_amount - 1;
	int neurons_lastlayer_amount = nnet->getNeuronsAmountLayer(layers_amount - 1);
	std::vector<std::vector<double>> deltas;
	deltas.resize(layers_amount);
	std::vector<double> vec_last_output = nnet->getLastNetOutput();
	std::vector<double> vec_error_last;
	vec_error_last.resize(neurons_lastlayer_amount);
	deltas.at(layers_amount - 1).resize(neurons_lastlayer_amount);
	std::thread th, th1, th2, th3, th4, th5, th6, th7;
	// error
	printf("Output...");
	b.start();
	int from = 0;// output
	int to = neurons_lastlayer_amount;
	th = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, (to / 8)); });
	th1 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8), (to / 8) * 2); });
	th2 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 2, (to / 8) * 3); });
	th3 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 3, (to / 8) * 4); });
	
	th4 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 4, (to / 8) * 5); });
	th5 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 5, (to / 8) * 6); });
	th6 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 6, (to / 8) * 7); });
	th7 = std::thread([this, nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to] { this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, (to / 8) * 7, to); });
	
	th.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
	b.stop();
	printf("Done");
	b.show(" ");
	printf("Hidden...");
	b.start();
	for (int i = hidden_layers_amount; i > 0; i--) // hidden
	{
		from = 0;
		to = nnet->getNeuronsAmountLayer(i - 1);
		deltas.at(i - 1).resize(to);
		th = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, from, (to / 8)); });
		th1 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8), (to / 8) * 2); });
		th2 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 2, (to / 8) * 3); });
		th3 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 3, (to / 8) * 4); });
		
		th4 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 4, (to / 8) * 5); });
		th5 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 5, (to / 8) * 6); });
		th6 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 6, (to / 8) * 7); });
		th7 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadErrorHidden(nnet, &deltas, i, (to / 8) * 7, to); });
		
		th.join();
		th1.join();
		th2.join();
		th3.join();
		th4.join();
		th5.join();
		th6.join();
		th7.join();
	}
	b.stop();
	printf("Done");
	b.show(" ");
	printf("Updating...\n");
	printf("Output...");
	b.start();
	// update
	from = 0;// output
	to = neurons_lastlayer_amount;
	th = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, from, (to / 8)); });
	th1 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8), (to / 8) * 2); });
	th2 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 2, (to / 8) * 3); });
	th3 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 3, (to / 8) * 4); });

	th4 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 4, (to / 8) * 5); });
	th5 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 5, (to / 8) * 6); });
	th6 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 6, (to / 8) * 7); });
	th7 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateOutput(nnet, &deltas, (to / 8) * 7, to); });

	th.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
	b.stop();
	printf("Done");
	b.show(" ");
	printf("Hidden...");
	b.start();
	for (int i = hidden_layers_amount - 1; i > 0; i--) // hidden
	{
		from = 0;
		to = nnet->getNeuronsAmountLayer(i);
		th = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, from, (to / 8)); });
		th1 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8), (to / 8) * 2); });
		th2 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 2, (to / 8) * 3); });
		th3 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 3, (to / 8) * 4); });

		th4 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 4, (to / 8) * 5); });
		th5 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 5, (to / 8) * 6); });
		th6 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 6, (to / 8) * 7); });
		th7 = std::thread([this, nnet, &deltas, i, from, to] { this->startThreadUpdateHidden(nnet, &deltas, i, (to / 8) * 7, to); });

		th.join();
		th1.join();
		th2.join();
		th3.join();
		th4.join();
		th5.join();
		th6.join();
		th7.join();
	}
	b.stop();
	printf("Done");
	b.show(" ");
	printf("Input...");
	b.start();
	from = 0; // input
	to = nnet->getNeuronsAmountLayer(0);
	th = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, from, (to / 8)); });
	th1 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8), (to / 8) * 2); });
	th2 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 2, (to / 8) * 3); });
	th3 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 3, (to / 8) * 4); });

	th4 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 4, (to / 8) * 5); });
	th5 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 5, (to / 8) * 6); });
	th6 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 6, (to / 8) * 7); });
	th7 = std::thread([this, nnet, &deltas, from, to] { this->startThreadUpdateInput(nnet, &deltas, (to / 8) * 7, to); });

	th.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
	b.stop();
	printf("Done");
	b.show(" ");
}
void Backpropagation::NoThread(NeuralNetBase *nnet, double learning_rate, const std::vector<double> &desired)
{
	this->learning_rate = learning_rate;
	int layers_amount = nnet->getLayersAmount();
	int hidden_layers_amount = layers_amount - 1;
	int neurons_lastlayer_amount = nnet->getNeuronsAmountLayer(layers_amount - 1);
	std::vector<std::vector<double>> deltas;
	deltas.resize(layers_amount);
	std::vector<double> vec_last_output = nnet->getLastNetOutput();
	std::vector<double> vec_error_last;
	vec_error_last.resize(neurons_lastlayer_amount);
	deltas.at(layers_amount - 1).resize(neurons_lastlayer_amount);
	// error
	int from = 0;// output
	int to = neurons_lastlayer_amount;
	this->startThreadErrorOutput(nnet, &vec_error_last, &vec_last_output, &deltas, desired, from, to);

	for (int i = hidden_layers_amount; i > 0; i--) // hidden
	{
		from = 0;
		to = nnet->getNeuronsAmountLayer(i - 1);
		deltas.at(i - 1).resize(to);
		this->startThreadErrorHidden(nnet, &deltas, i, from, to);
	}

	// update
	from = 0;// output
	to = neurons_lastlayer_amount;
	this->startThreadUpdateOutput(nnet, &deltas, from, to);

	for (int i = hidden_layers_amount - 1; i > 0; i--) // hidden
	{
		from = 0;
		to = nnet->getNeuronsAmountLayer(i);
		this->startThreadUpdateHidden(nnet, &deltas, i, from, to);
	}
	from = 0; // input
	to = nnet->getNeuronsAmountLayer(0);
	this->startThreadUpdateInput(nnet, &deltas, from, to);
}


//error
//output
void Backpropagation::startThreadErrorOutput(NeuralNetBase *nnet, std::vector<double> *vec_error_last, std::vector<double> *vec_last_output, std::vector<std::vector<double>> *deltas, const std::vector<double> &desired, int from, int to)
{
	int layers_amount = nnet->getLayersAmount();
	for (int j = from; j < to; j++) // output
	{
		vec_error_last->at(j) = desired.at(j) - vec_last_output->at(j);
		deltas->at(layers_amount - 1).at(j) = nnet->getNeuronIndexLayer(j, layers_amount - 1)->getLastActivationDerivative() * vec_error_last->at(j);
	}
}
//hidden
void Backpropagation::startThreadErrorHidden(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int layer, int from, int to)
{
	double sum = 0.0;
	for (int j = from; j < to; j++)
	{
		int s = nnet->getNeuronsAmountLayer(layer);
		for (int h = 0; h < s; h++)
		{
			sum += (nnet->getNeuronIndexLayer(h, layer)->getVecInputWeights().at(j) * deltas->at(layer).at(h));
		}
		deltas->at(layer - 1).at(j) = nnet->getNeuronIndexLayer(j, layer - 1)->getLastActivationDerivative() * sum;
		sum = 0.0;
	}
}
//update
//output
void Backpropagation::startThreadUpdateOutput(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int from, int to)
{
	int layers_amount = nnet->getLayersAmount();
	for (int i = from; i < to; i++)
	{
		int s = nnet->getNeuronsAmountLayer(layers_amount - 2);
		for (int j = 0; j < s; j++)
		{
			nnet->updateWeightNeuronLayer(this->learning_rate * (deltas->at(layers_amount - 1).at(i) * nnet->getNeuronIndexLayer(j, layers_amount - 2)->getLastActivationValue()), j, i, layers_amount - 1);
		}
		nnet->updateBiasNeuronLayer(this->learning_rate * deltas->at(layers_amount - 1).at(i) * -1.0, i, layers_amount - 1);
	}

}
//hidden
void Backpropagation::startThreadUpdateHidden(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int layer, int from, int to)
{
	for (int j = from; j < to; j++)
	{
		int ss = nnet->getNeuronsAmountLayer(layer - 1);
		for (int h = 0; h < ss; h++)
		{
			nnet->updateWeightNeuronLayer(learning_rate * deltas->at(layer).at(j) * nnet->getNeuronIndexLayer(h, layer - 1)->getLastActivationValue(), h, j, layer);
		}
		nnet->updateBiasNeuronLayer(learning_rate * deltas->at(layer).at(j) * -1.0, j, layer);
	}
}
//input
void Backpropagation::startThreadUpdateInput(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int from, int to)
{
	for (int i = from; i < to; i++) // input
	{
		int ss = nnet->getLastNetInput().size();
		for (int j = 0; j < ss; j++)
		{
			nnet->updateWeightNeuronLayer(this->learning_rate * deltas->at(0).at(i) * nnet->getLastNetInput().at(j), j, i, 0);
		}
		nnet->updateBiasNeuronLayer(this->learning_rate * deltas->at(0).at(i) * -1.0, i, 0);
	}
}