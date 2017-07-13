#include "Activation.h"

Activation::Activation(std::string activation_name)
{
	this->setActivation(activation_name);
}

Activation::~Activation()
{}

void Activation::setActivation(std::string activation_name)
{
	this->activation_name = activation_name;
}

std::string Activation::getActivationName()
{
	return this->activation_name;
}


double Activation::calcActivation(const std::string &activation_name, double sum_out)
{
	if(activation_name == "Sigmoid")
	{
		return this->actv_Sigmoid(sum_out);
	}
	if(activation_name == "Tanh")
	{
		return this->actv_Tanh(sum_out);
	}
	if(activation_name == "Linear")
	{
		return this->actv_Linear(sum_out);
	}
	if(activation_name == "ReLU")
	{
		return this->actv_ReLU(sum_out);
	}
	if(activation_name == "ELU")
	{
		return this->actv_ELU(sum_out);
	}
	return 0.0;
}

double Activation::calcDerivative(const std::string &activation_name, double x)
{
	if(activation_name == "Sigmoid")
	{
		return this->deriv_Sigmoid(x);
	}
	if(activation_name == "Tanh")
	{
		return this->deriv_Tanh(x);
	}
	if(activation_name == "Linear")
	{
		return this->deriv_Linear(x);
	}
	if(activation_name == "ReLU")
	{
		return this->deriv_ReLU(x);
	}
	if(activation_name == "ELU")
	{
		return this->deriv_ELU(x);
	}
	return 0.0;
}