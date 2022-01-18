//
// Created by pcosme on 14/01/2022.
//

#include "../src/ODEpoint.h"
#include "../src/ODEsolver.h"
#include "../src/NonlinearSolver.h"

#include <fstream>
#include <iomanip>

using namespace std;

#define ODE_STEP 1E-3
#define ODE_TMAX 20

double BlasiusEnd(double shear){
	vector<double> v0_blasius{0,0,shear};
	ODEpoint ponto_inicial_blasius(0, v0_blasius);
	ODEsolver metodo_blasius(ponto_inicial_blasius);
	metodo_blasius.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	metodo_blasius.SetFunction(1,[](ODEpoint x) { return x.X()[2]; });
	metodo_blasius.SetFunction(2,[](ODEpoint x) { return -0.5*x.X()[2]*x.X()[0]; });
	metodo_blasius.SetTmax(ODE_TMAX);
	metodo_blasius.Heun(ODE_STEP);
	return metodo_blasius.Sol().back().X()[1]-1;
}

int main() {

	NonlinearSolver ShootingSolver = NonlinearSolver();
	ShootingSolver.SetTolerance(1E-10);
	ShootingSolver.SetIterations(20);

	double solution_IVP = ShootingSolver.BissectionMethod(BlasiusEnd,.0,1.0);

//	double solution_IVP = ShootingSolver.RegulaFalsi(BlasiusEnd,.0,1.0);

	cout << "solução shooting method:\t"<<solution_IVP<<endl;
	cout << "solução tabelada:\t0.332057336515196"<<endl;

	for (int i = 0; i <ShootingSolver.Iter().size() ; ++i) {
		cout <<"iteração #\t"<<i+1<<"\t"<< fixed << setprecision(9)  << ShootingSolver.Iter().at(i) << endl;
	}



	vector<double> v0_blasius{0,0,solution_IVP};
	ODEpoint ponto_inicial_blasius(0, v0_blasius);
	ODEsolver blasius(ponto_inicial_blasius);
	blasius.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	blasius.SetFunction(1,[](ODEpoint x) { return x.X()[2]; });
	blasius.SetFunction(2,[](ODEpoint x) { return -0.5*x.X()[2]*x.X()[0]; });
	blasius.SetTmax(ODE_TMAX);
	vector<ODEpoint> solution_blasius=blasius.Heun(ODE_STEP);
	blasius.FileOutput();

	return 0;
}
