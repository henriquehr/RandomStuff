#pragma once
#include <chrono>
#include <iostream>
#include <string>

class Benchmark
{
public:
	Benchmark() {};
	~Benchmark() {};
	void start() { this->time_start = std::chrono::high_resolution_clock::now(); };
	void stop() { this->time_stop = std::chrono::high_resolution_clock::now(); };
	void show(const std::string &txt)
	{
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start);
		std::cout << txt << "" << time_span.count() << std::endl;
	};
private:
	std::chrono::high_resolution_clock::time_point time_start;
	std::chrono::high_resolution_clock::time_point time_stop;
};
