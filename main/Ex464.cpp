#include <utility>
#include <iostream>

#include "../src/ODEpoint.h"
#include "../src/ODEsolver.h"
#include "../src/NonlinearSolver.h"

#include <fstream>
#include <iomanip>

using namespace std;

#define ODE_STEP 1E-3
#define ODE_TMAX 10

int main() {


	double drag=0.0535;


	vector<double> cond_init{1,0};
	ODEpoint ponto_inicial(0, cond_init);
	ODEsolver Queda(ponto_inicial);
	Queda.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	Queda.SetFunction(1,[=](ODEpoint x) { return -1.0-drag*x.X()[1]; });
	Queda.SetTmax(ODE_TMAX);
	vector<ODEpoint> Queda_sol=Queda.Heun(ODE_STEP);
	Queda.FileOutput();

	return 0;
}