//
// Created by pcosme on 15/01/2022.
//

#include "NonlinearSolver.h"

int NonlinearSolver::GetIterations() const {
	return Iterations;
}

void NonlinearSolver::SetIterations(int number_of_iterations) {
Iterations=number_of_iterations;
}

double NonlinearSolver::SecantMethod(function<double(double)> func, double x0, double x1) {
	double X1,X2,next,root=0;
	solutions.push_back(x0);
	solutions.push_back(x1);

	for (int i = 0; i < Iterations; ++i) {
		X1 = solutions.end()[-1];
		X2 = solutions.end()[-2];
		next = X1-func(X1)*(X1-X2)/(func(X1)-func(X2));
		solutions.push_back(next);
	}
	root=solutions.back();
	return root;
}

double NonlinearSolver::BissectionMethod(function<double(double)> func, double xa, double xb) {
	double a,b,midpoint= 0.5*(xa+xb),root=0;
	a=xa;
	b=xb;
	for (int i = 0; i < Iterations; ++i) {
		midpoint = 0.5*(a+b);
		solutions.push_back(midpoint);
		if( abs(func(midpoint))<=Tolerance || 0.5*(b-a)<=Tolerance ){
			root=midpoint;
			break;
		}else{
			if( func(midpoint)*func(a) > 0 ){
				a=midpoint;
			}else{
				b=midpoint;
			}
		}
	}
	root=midpoint;
	return root;
}


double NonlinearSolver::RegulaFalsi(function<double(double)> func, double xa, double xb) {
	double a,b,midpoint= 0.5*(xa+xb),root=0;

	a=xa;
	b=xb;
	for (int i = 0; i < Iterations; ++i) {
		midpoint = (a*func(b)-b*func(a))/(func(b)-func(a));
		solutions.push_back(midpoint);
		if( abs(func(midpoint))<=Tolerance || 0.5*(b-a)<=Tolerance ){
			root=midpoint;
			break;
		}else{
			if( func(midpoint)*func(a) > 0 ){
				a=midpoint;
			}else{
				b=midpoint;
			}
		}
	}
	root=midpoint;
	return root;
}

double NonlinearSolver::GetTolerance() const {
	return Tolerance;
}

void NonlinearSolver::SetTolerance(double tol) {
	Tolerance=tol;
}

vector<double> &NonlinearSolver::Iter() {
	return solutions;
}
