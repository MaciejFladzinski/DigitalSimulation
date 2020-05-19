#include "generators.h"

#include <fstream>

Generators::Generators(int kernel)
{
	kernel_ = kernel;
}

Generators::~Generators()
{
}

double Generators::Rand()
{
	int h = floor(kernel_ / kQ);
	kernel_ = kA * (kernel_ - kQ * h) - kR * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(kM);
	return kernel_ / kM;
}

int Generators::Rand(double min, double max)
{
	return Rand() * (max - min) + min;
}

int Generators::RandExp(double lambda)
{
	auto k = Rand();

	return -(1.0 / lambda) * log(k);
}

int Generators::RandZeroOne(double p)
{
	auto k = Rand();

	if (k < p)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Generators::GetKernel()
{
	return kernel_;
}
