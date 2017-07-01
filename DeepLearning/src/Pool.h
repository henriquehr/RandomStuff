#pragma once
#include <vector>

class Pool
{
public:
	Pool();
	~Pool();
	std::vector<std::vector<double>> maxPool(const std::vector<std::vector<double>>& m, int pool_size);
	std::vector<std::vector<double>> meanPool(const std::vector<std::vector<double>>& m, int pool_size);
	void setSize(int size);
private:
	std::vector<std::vector<double>> pool;
	int poolSize;
};

