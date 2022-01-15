//
// Created by pcosme on 14/01/2022.
//

#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ODEpoint.h"
#include <math.h>
#include <fstream>
using namespace std;


class ODEsolver {

public:
	ODEsolver() = default;
	~ODEsolver() = default;
	explicit ODEsolver(ODEpoint x_0);
	int GetRank() const;
	int GetTmax() const;
	int Getdt() const;
	void SetTmax(double tmax) ;

	vector<ODEpoint>& Euler(double step=1E-3);
	vector<ODEpoint>& Heun(double step=1E-3);
	vector<ODEpoint>& ExplicitMidpoint(double step=1E-3);

	void SetFunction(int index, function<double(ODEpoint)> func);
	ODEpoint EvalFunc(ODEpoint arg);

	void FileOutput();

	vector<ODEpoint>& Sol();

private:
	int dim;
	double dt=1E-3;
	double Tmax=1;
	ODEpoint xi;
	vector<ODEpoint> solution;
	function<double(ODEpoint)> * f;
};


#endif //ODESOLVER_H

