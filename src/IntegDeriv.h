//
// Created by pcosme on 18/01/2022.
//

#ifndef INTEGDERIV_H
#define INTEGDERIV_H

#include <cmath>
#include <utility>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;



static bool abs_compare(double a, double b)
{
	return (std::abs(a) < std::abs(b));
}


class IntegDeriv {

public:
	IntegDeriv(function<double(double)>& );
	~IntegDeriv() = default;
// integration methods
	void TrapezoidalRule(double xi, double xf, double &Integral, double &Error);
	void SimpsonRule(double xi, double xf, double &Integral, double &Error);
	void MonteCarlo(double xi, double xf, int samples, double &Integral, double &Error);

	void Numerical2ndDerivative(double xi, double xf,vector<double>& df);
	void Numerical4thDerivative(double xi, double xf,vector<double>& df);

	void SetStep(double );
	double GetStep() const;

private:
	function<double(double)> func;
	int NumberOfSteps(double xi, double xf) const;

	double xstep;
};


#endif //INTEGDERIV_H



