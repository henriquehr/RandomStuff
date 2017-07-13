#include "ImageFeatureExtractor.h"
#include "NeuralNetBase.h"
#include "PerceptronNet.h"
#include "TrainBase.h"
#include "Backpropagation.h"
#include "Benchmark.h"

int main() {
	Benchmark b;

	char *filename = "test.png";
	ImageFeatureExtractor iFE;
	std::vector<std::vector<std::vector<double>>> img;
	std::vector<std::vector<std::vector<double>>> conv;
	std::vector<std::vector<std::vector<double>>> pool;
	std::vector<std::vector<std::vector<double>>> last;

	img = iFE.loadImage(filename);
	if (img.at(0).size() != 0) {
		conv = iFE.convolve(img, 2);
		conv = iFE.convolve(conv, 2);
		pool = iFE.pool(conv, 2);
		conv = iFE.convolve(pool, 2);
		conv = iFE.convolve(conv, 2);
		pool = iFE.pool(conv, 2);
		conv = iFE.convolve(pool, 2);
		conv = iFE.convolve(conv, 2);
		conv = iFE.convolve(conv, 2);
		pool = iFE.pool(conv, 2);
		pool = iFE.pool(pool, 2);
		last = pool;
		iFE.saveImage(conv, "ImgOut/Convolved.png");
		iFE.saveImage(pool, "ImgOut/Pool.png");
	}

	std::vector<double> input(last.at(0).size() * last.at(0).at(0).size() * 3);
	int inputIdx = 0;
	for (int i = 0; i < last.at(0).size(); i++)
	{
		for (int j = 0; j < last.at(0).at(i).size(); j++)
		{
			input.at(inputIdx) = last.at(0).at(i).at(j);
			inputIdx++;
			input.at(inputIdx) = last.at(1).at(i).at(j);
			inputIdx++;
			input.at(inputIdx) = last.at(2).at(i).at(j);
			inputIdx++;
		}
	}

	std::vector<std::vector<std::vector<double>>>().swap(img);
	std::vector<std::vector<std::vector<double>>>().swap(conv);
	std::vector<std::vector<std::vector<double>>>().swap(pool);
	std::vector<std::vector<std::vector<double>>>().swap(last);

	NeuralNetBase *nn = new PerceptronNet();
	TrainBase *t = new Backpropagation();
	std::vector<double> desired = { 0.9,0.1,0.2,-0.5,0.9 };
	nn->setLayersAmount(2);
	//nn->createNeuronsLayer(128, 0, "Tanh", input.size());
	nn->createNeuronsLayer(2048, 0, "Sigmoid", input.size());
	//nn->createNeuronsLayer(1024, 2, "Sigmoid", 2048);
	nn->createNeuronsLayer(5, 1, "Sigmoid", 2048);
	nn->generateWeights(-1, 1);
	std::vector<double> out;
	for (int i = 0; i < 20; i++)
	{
		out = nn->step(input);
		t->start(nn, 0.01, desired);
		printf("Out %d: ", i);
		for (int i = 0; i < out.size(); i++)
		{
			std::cout << out.at(i) << " ";
		}
		printf("\n");
	}

	delete nn;

	std::cout << std::endl;

	system("pause");
	return 0;
}
