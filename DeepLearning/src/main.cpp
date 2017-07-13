//#include "PerceptronNet.h"
//#include "Benchmark.h"
//#include "Backpropagation.h"
//#include "RecurrentNet.h"
//
//void setup(const std::vector<double> &input, NeuralNetBase *nn)
//{
//	Benchmark bench;
//
//	int hidden1 = 20;
//	int hidden2 = 20;
//	int hidden3 = 20;
//	int out = 9;
//
//	bench.start();
//	nn->setLayersAmount(4);
//	nn->createNeuronsLayer(hidden1, 0, "Tanh", input.size());
//	nn->createNeuronsLayer(hidden2, 1, "Tanh", hidden1);
//	nn->createNeuronsLayer(hidden3, 2, "Tanh", hidden2);
//	nn->createNeuronsLayer(out, 3, "Tanh", hidden3);
//	nn->generateWeights(-1, 1);
//	bench.stop();
//	bench.show("Setup");
//}
//
//int main(int argc, char *argv[])
//{
//	Benchmark bench1, bench2;
//	TrainBase *backprop = new Backpropagation();
//	NeuralNetBase *perc = new RecurrentNet(0);
//	//LSTMNet *lstm = new LSTMNet(0);
//	//NeuronBase * l =  new LSTMCell(" ", 0);
//	//std::cout << l->getBiasWeightInput() << std::endl;
//	//delete l;
//	//system("pause");
//	//return 0;
//
//	std::vector<double> out;
//	std::vector<double> input = {0.4, 0.5, 0.3, 0.1, 0.3, 0.7, 0.9, -1 ,0,0,0,0,0};
//	std::vector<double> desired = {0.17, 0.9, 0.6, 0.1, 1, 0.1, 1, 0.4,-0.7};
//	double learning_rate = 0.1;
//	//setup(input, lstm);
//	//out = lstm->step(input);
//	//std::cout << "Out1: " << out.at(0) << " | " << "Out2: " << out.at(1) << " | " << "Out3: " << out.at(2) << std::endl;
//	//system("pause");
//	//return EXIT_SUCCESS;
//
//	setup(input, perc);
//	bench1.start();
//	for(int i = 0; i < 2000; i++)
//	{
//		//msg.Message("Propagating...");
//		out = perc->step(input);
//		//msg.Message("Backpropagating...");
//		//bench2.start();
//		backprop->start(perc, learning_rate, desired);
//		//bench2.stop();
//		//bench2.show("Backpropagation");
//		//std::cout << "Error1: " << (desired.at(0) - out.at(0)) << " | " << "Error2: " << (desired.at(1) - out.at(1)) << " | " << "Error3: " << (desired.at(2) - out.at(2)) << std::endl;
//	}
//	for(int i = 0; i < out.size(); ++i)
//	{
//		std::cout << "O" << i << ": " << out.at(i) << " | ";
//	}
//	std::cout << std::endl;
//	for(int i = 0; i < out.size(); ++i)
//	{
//		std::cout << "D" << i << ": " << desired.at(i) << " | ";
//	}
//	std::cout << std::endl;
//	bench1.stop();
//	bench1.show("LOOP");
//
//	//perc->showNetWeights();
//
//	//msg.Message(perc->getLayersAmount());
//	//msg.Message(out[0]);
//
//	std::cout << "Cleaning memory..." << std::endl;
//	system("pause");
//	//delete lstm;
//	delete perc;
//	delete backprop;
//	std::cout << "Memory cleaned" << std::endl;
//	//system("pause");
//	return EXIT_SUCCESS;
//}