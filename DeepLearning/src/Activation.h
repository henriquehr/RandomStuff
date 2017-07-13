#pragma once
#include <vector>

class Activation
{
public:
	explicit  Activation(std::string activation_name);
	~Activation();
	void setActivation(std::string actv_name);
	std::string getActivationName();
	double calcActivation(const std::string& activation_name, double sum_out);
	double calcDerivative(const std::string& activation_name, double x);
private:
	std::string activation_name;
	static double actv_Sigmoid(double sum_out) { return 1.0 / (1.0 + exp(-sum_out)); }; // (0,1)
	static double deriv_Sigmoid(double x) { double s = 1.0 / (1.0 + exp(-x)); return  s * (1 - s); };
	static double actv_Tanh(double sum_out) { return tanh(sum_out); }; // (-1,1)
	static double deriv_Tanh(double x) { double th = tanh(x); return 1 - th * th; };
	static double actv_Linear(double sum_out) { return sum_out; }; // (sum_out)
	static double deriv_Linear(double x) { return 1; };
	static double actv_ReLU(double sum_out) { return sum_out > 0.0 ? sum_out : 0.0; }; // (0,sum_out)
	static double deriv_ReLU(double x) { return x >= 0.0 ? 1 : 0.0; };
	/*def stablesoftmax(x):
    """Compute the softmax of vector x in a numerically stable way."""
    shiftx = x - np.max(x)
    exps = np.exp(shiftx)
    return exps / np.sum(exps)*/

	/*static std::vector<double> actv_Softmax(std::vector<double> sum_out)
	{
		int s = sum_out.size();
		std::vector<double> r;
		r.resize(s);
		double sum = 0.0;
		double max = r.at(0);
		for(int i = 0; i < s; ++i)
		{
			double t = sum_out.at(i);
			max = max < t ? t : max;
		}
		for(int i = 0; i < s; ++i)
		{
			int norm = sum_out.at(i) - max;
			r.at(i) = exp(norm);
			sum += r.at(i);
		}
		for(int i = 0; i < s; ++i)
		{
			r.at(i) = r.at(i) / sum;
		}
		return r;
	};
	static double deriv_Softmax(double x) { return 1.0; };*/
	//max(0,x)+min(0,alpha*(exp(x)-1))
	static double actv_ELU(double sum_out) { return sum_out > 0 ? sum_out : 1.0 * (exp(sum_out) - 1); }; // double alpha = 1.0;
	static double deriv_ELU(double x) { return x > 0.0 ? 1 : actv_ELU(x) + 1.0; }; // double alpha = 1.0;
};
