//
// Created by pcosme on 18/01/2022.
//



#include <TRandom3.h>
#include "IntegDeriv.h"

IntegDeriv::IntegDeriv(function<double(double)> &f) {
	func=f;
	xstep=0.01;
}

double IntegDeriv::GetStep() const {
	return xstep;
}

void IntegDeriv::SetStep(double h) {
	xstep=h;
}

void IntegDeriv::TrapezoidalRule(double xi, double xf, double &Integral, double &Error) {
	int N= this->NumberOfSteps(xi,xf);
	double sum=0.0,err=0.0;
	for (int k = 1; k <= N-1; ++k) {
		sum += func(xi+k*xstep);
	}
	Integral= xstep*(sum+0.5*(xi+xf));

	vector<double> d2fnum;
	this->Numerical2ndDerivative(xi,xf,d2fnum);
	auto max_derivative = *max_element(d2fnum.begin(), d2fnum.end(), abs_compare);
	err = pow(xstep,2)*(xf-xi)*max_derivative/12.0;

	Error=abs(err);
}

void IntegDeriv::SimpsonRule(double xi, double xf, double &Integral, double &Error) {
	int N= this->NumberOfSteps(xi,xf);
	double sum1=0.0,sum2=0.0,err=0.0;
	for (int k = 1; k <= N/2-1; ++k) {
		sum1 += func(xi+2*k*xstep);
	}
	for (int k = 1; k <= N/2; ++k) {
		sum2 += func(xi+(2*k-1)*xstep);
	}
	Integral= xstep*(2*sum1+4*sum2+(xi+xf))/3.0;

	vector<double> d4fnum;
	this->Numerical4thDerivative(xi,xf,d4fnum);
	auto max_derivative = *max_element(d4fnum.begin(), d4fnum.end(), abs_compare);
	err = pow(xstep,4)*(xf-xi)*max_derivative/180.0;

	Error=abs(err);
}

int IntegDeriv::NumberOfSteps(double xi, double xf) const {
	return static_cast<int>( (xf-xi)/xstep );
}

void IntegDeriv::MonteCarlo(double xi, double xf,int samples, double &Integral, double &Error) {
	double sum=0.0,err=0.0,var=0.0,xrand;
	gRandom = new TRandom3(0);

	for (int i = 0; i <= samples; ++i) {
		xrand=	gRandom->Uniform(xi,xf);
		sum += func(xrand);
		var += pow(func(xrand),2);
	}

	Integral= (xf-xi)*sum/samples;
	Error=((xf-xi)/sqrt(samples))*sqrt(var/samples-pow(sum/samples,2));
}

void IntegDeriv::Numerical2ndDerivative(double xi, double xf, vector<double> &df) {
	int N= this->NumberOfSteps(xi,xf);
	double x,deriv;
	for (int i = 0; i <= N ; ++i) {
		x= xi + i*xstep;
		deriv=(func(x-xstep)-2.0*func(x)+func(x+xstep))/(xstep*xstep);
		df.push_back(deriv);
	}
}

void IntegDeriv::Numerical4thDerivative(double xi, double xf, vector<double> &df) {
	int N= this->NumberOfSteps(xi,xf);
	double x,deriv;
	for (int i = 0; i <= N ; ++i) {
		x= xi + i*xstep;
		deriv=(func(x-2*xstep)-4.0*func(x-xstep)+6.0*func(x)-4.0*func(x+xstep)+func(x+2*xstep))/pow(xstep,4);
		df.push_back(deriv);
	}
}
