//
// Created by pcosme on 14/01/2022.
//

#include "ODEsolver.h"


ODEsolver::ODEsolver(ODEpoint x_0) {
	xi=x_0;
	dim=xi.X().size();
	f = new function<double(ODEpoint)>[dim]();
}

int ODEsolver::GetRank() const { return dim;}

void ODEsolver::SetFunction(int index, function<double(ODEpoint)> func) {
	f[index]= func;
}



int ODEsolver::GetTmax() const {
	return Tmax;
}

int ODEsolver::Getdt() const {
	return dt;
}

void ODEsolver::SetTmax(double tmax) {
	Tmax=tmax;
}

ODEpoint ODEsolver::EvalFunc(ODEpoint arg) {
	ODEpoint result(arg.T(),arg.X());
	for (int i = 0; i < dim; ++i) {
		result.X()[i]=f[i](arg);
	}
	return result;
}


vector<ODEpoint>& ODEsolver::Euler(double step) {
	solution.clear();
	dt=step;
	solution.push_back(xi);
	ODEpoint newpoint(xi.T(),xi.X());
	ODEpoint oldpoint(xi.T(),xi.X());

	double time=xi.T();
	while(time <= Tmax) {
		oldpoint = solution.back();
		for (int i = 0; i < dim ; ++i) {
			newpoint.X()[i] = oldpoint.X()[i]+ dt*f[i](oldpoint);
		}
		time+=dt;
		newpoint.T()=time;
		solution.push_back(newpoint);
	}
	return solution;
}

vector<ODEpoint>& ODEsolver::Heun(double step) {
	dt=step;
	solution.clear();
	solution.push_back(xi);
	ODEpoint newpoint(xi.T(),xi.X());
	ODEpoint oldpoint(xi.T(),xi.X());
	ODEpoint auxpoint(xi.T(),xi.X());

	double time=xi.T();
	while(time <= Tmax) {
		oldpoint = solution.back();
		for (int i = 0; i < dim ; ++i) {
			auxpoint.X()[i] = oldpoint.X()[i]+ dt*f[i](oldpoint);
		}
		auxpoint.T()=time+dt;
		for (int i = 0; i < dim ; ++i) {
			newpoint.X()[i] = oldpoint.X()[i]+ 0.5*dt*( f[i](oldpoint) + f[i](auxpoint) );
		}
		time+=dt;
		newpoint.T()=time;
		solution.push_back(newpoint);
	}
	return solution;
}

vector<ODEpoint>& ODEsolver::ExplicitMidpoint(double step) {
	dt=step;
	solution.clear();
	solution.push_back(xi);
	ODEpoint newpoint(xi.T(),xi.X());
	ODEpoint oldpoint(xi.T(),xi.X());
	ODEpoint auxpoint(xi.T(),xi.X());

	double time=xi.T();
	while(time <= Tmax) {
		oldpoint = solution.back();
		for (int i = 0; i < dim ; ++i) {
			auxpoint.X()[i] = oldpoint.X()[i]+ 0.5*dt*f[i](oldpoint);
		}
		auxpoint.T()=time+dt*0.5;
		for (int i = 0; i < dim ; ++i) {
			newpoint.X()[i] = oldpoint.X()[i]+ dt*( f[i](auxpoint) );
		}
		time+=dt;
		newpoint.T()=time;
		solution.push_back(newpoint);
	}
	return solution;
}

void ODEsolver::FileOutput() {
	ofstream outputfile;
	outputfile.open ("ODEsolution.dat");
	for (int i = 0; i < solution.size(); ++i) {
		outputfile << solution.at(i).T() << "\t";
		for (int k = 0; k < dim; ++k) {
			outputfile <<  solution.at(i).X()[k] << "\t";
		}
		outputfile << endl;
	}
	outputfile.close();
}

vector<ODEpoint> &ODEsolver::Sol() {
	return solution;
}
