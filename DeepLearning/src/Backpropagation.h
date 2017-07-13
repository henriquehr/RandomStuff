#pragma once
#include <vector>
#include "NeuralNetBase.h"
#include "TrainBase.h"


class Backpropagation :public TrainBase
{
public:
	Backpropagation();
	~Backpropagation();
	void start(NeuralNetBase* nnet, double learning_rate, const std::vector<double>& desired) override;
	void YesThread(NeuralNetBase * nnet, double learning_rate, const std::vector<double>& desired);
	void NoThread(NeuralNetBase * nnet, double learning_rate, const std::vector<double>& desired);
	void startThreadErrorOutput(NeuralNetBase *nnet, std::vector<double> *vec_error_last, std::vector<double> *vec_last_output, std::vector<std::vector<double>> *deltas, const std::vector<double> &desired, int from, int to);
	void startThreadErrorHidden(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int layer, int from, int to);
	void startThreadUpdateOutput(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int from, int to);
	void startThreadUpdateHidden(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int layer, int from, int to);
	void startThreadUpdateInput(NeuralNetBase *nnet, std::vector<std::vector<double>> *deltas, int from, int to);
};
