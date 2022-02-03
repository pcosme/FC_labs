#include <utility>
#include <iostream>

#include "../src/ODEpoint.h"
#include "../src/ODEsolver.h"
#include "../src/NonlinearSolver.h"

#include <fstream>
#include <iomanip>


#include "TGraph.h"
#include "TCanvas.h"

#include "TRootCanvas.h"
#include "TApplication.h"


using namespace std;

#define ODE_STEP 1E-2
#define ODE_TMAX 200

int main() {



	double drag=0.0535;
	vector<double> cond_init{1,0};
	ODEpoint ponto_inicial(0, cond_init);
	ODEsolver Queda(ponto_inicial);
	Queda.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	Queda.SetFunction(1, [=](ODEpoint x) { return -1.0 - drag * x.X()[1]; });
	Queda.SetTmax(ODE_TMAX);
	vector<ODEpoint> Queda_sol=Queda.Heun(ODE_STEP);
	Queda.FileOutput();



	TApplication app("app", nullptr, nullptr);

	TCanvas *c1 = new TCanvas("c1","X vs. time",200,10,800,500);
	TGraph * points_graph = new TGraph();

	for (int i = 0; i < Queda_sol.size(); ++i) {
		points_graph->AddPoint(Queda_sol.at(i).T(),Queda_sol.at(i).X()[0]);
	}
	points_graph->SetLineColor(2);
	points_graph->Draw("AC");


	c1->Update();



	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();


	return 0;
}