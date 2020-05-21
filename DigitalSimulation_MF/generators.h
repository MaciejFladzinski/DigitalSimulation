#ifndef GENERATORS_H
#define GENERATORS_H

#include <string>
#include <cmath>

class Generators
{
public:
	Generators(int kernel);
	~Generators();

	double Rand();
	int Rand(double min, double max);
	int RandExp(double lambda);
	int RandZeroOne(double p);

	int GetKernel();

private:
	int kernel_;
	const double kM = 2147483647.0;
	static const int kA = 16807;
	static const int kQ = 127773;
	static const int kR = 2836;
};

#endif GENERATORS_Hf