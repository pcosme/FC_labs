//
// Created by pcosme on 15/01/2022.
//

#ifndef NONLINEARSOLVER_H
#define NONLINEARSOLVER_H

#include <utility>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;


class NonlinearSolver {
public:
	NonlinearSolver()=default;
	~NonlinearSolver()=default;

	double SecantMethod(function<double(double)> func,double x0,double x1);
	double BissectionMethod(function<double(double)> func,double xa,double xb);
	double RegulaFalsi(function<double(double)> func,double xa,double xb);

	void SetIterations(int );
	int GetIterations() const;
	void SetTolerance(double );
	double GetTolerance() const;

	vector<double>& Iter();

private:
	int Iterations=100;
	double Tolerance=5E-4;
	vector<double> solutions;
};


#endif //NONLINEARSOLVER_H
