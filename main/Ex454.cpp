#include <utility>
#include <iostream>

#include <fstream>
#include <iomanip>
#include <math.h>
#include "../src/IntegDeriv.h"

using namespace std;


int main() {

	function<double(double)> funcao=[](double x) { return 1.0/(1.0+x*x); };

	IntegDeriv Integracao(funcao);

	double IntResult,ErrResult;


	cout<<"Integral Tabelado\t"<<  0.25*M_PI <<endl;

	Integracao.SetStep(1E-2);
	Integracao.TrapezoidalRule(0,1,IntResult,ErrResult);
	cout<<"Integral Trapezoidal\t"<< IntResult<<"\t";
	cout<<"Erro\t"<< ErrResult <<endl;
	Integracao.SetStep(1E-2);
	Integracao.SimpsonRule(0,1,IntResult,ErrResult);
	cout<<"Integral Simpson\t"<< IntResult<<"\t";
	cout<<"Erro\t"<< ErrResult <<endl;

	Integracao.MonteCarlo(0,1,100,IntResult,ErrResult);
	cout<<"Integral Monte Carlo\t"<< IntResult<<"\t";
	cout<<"Erro\t"<< ErrResult <<endl;
	Integracao.MonteCarlo(0,1,1000,IntResult,ErrResult);
	cout<<"Integral Monte Carlo\t"<< IntResult<<"\t";
	cout<<"Erro\t"<< ErrResult <<endl;
	Integracao.MonteCarlo(0,1,10000,IntResult,ErrResult);
	cout<<"Integral Monte Carlo\t"<< IntResult<<"\t";
	cout<<"Erro\t"<< ErrResult <<endl;
	return 0;
}

