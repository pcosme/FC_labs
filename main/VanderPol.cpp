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
#define ODE_TMAX 20

int main() {




	double mu=2.0;
	vector<double> cond_init{-1,4};
	//vector<double> cond_init{1,0};
	ODEpoint ponto_inicial(0, cond_init);
	ODEsolver VanDerPol(ponto_inicial);
	VanDerPol.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	VanDerPol.SetFunction(1, [=](ODEpoint x) { return mu * (1.0 - x.X()[0] * x.X()[0]) * x.X()[1] - x.X()[0]; });
	VanDerPol.SetTmax(ODE_TMAX);
	vector<ODEpoint> VanDerPol_sol=VanDerPol.Heun(ODE_STEP);
	VanDerPol.FileOutput();




	TApplication app("app", nullptr, nullptr);

	TCanvas *c1 = new TCanvas("c1","X vs. time",200,10,800,500);
	TGraph * points_graph = new TGraph();

	for (int i = 0; i < VanDerPol_sol.size(); ++i) {
		points_graph->AddPoint(VanDerPol_sol.at(i).T(),VanDerPol_sol.at(i).X()[0]);
	}
	points_graph->SetLineColor(2);
	points_graph->Draw("AC");


	c1->Update();


	TCanvas *c2 = new TCanvas("c2","Phase Space",200,10,800,500);
	TGraph * points_phase_space = new TGraph();
	for (int i = 0; i < VanDerPol_sol.size(); ++i) {
		points_phase_space->AddPoint(VanDerPol_sol.at(i).X()[0],VanDerPol_sol.at(i).X()[1]);
	}
	points_phase_space->SetLineColor(2);
	points_phase_space->Draw("AC");
	c2->Update();




	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();


	return 0;
}
