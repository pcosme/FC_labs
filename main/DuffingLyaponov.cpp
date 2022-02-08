#include <utility>
#include <iostream>

#include "../src/ODEpoint.h"
#include "../src/ODEsolver.h"
#include "../src/NonlinearSolver.h"

#include <fstream>
#include <iomanip>


#include "TGraph.h"

#include "TAxis.h"
#include "TCanvas.h"

#include "TRootCanvas.h"
#include "TApplication.h"


using namespace std;

#define ODE_STEP 1E-2
#define ODE_TMAX 800

int main() {

	double gamma=0.5;
	vector<double> cond_init1{1,0.5};
	ODEpoint ponto_inicial1(0, cond_init1);
	ODEsolver Duffing1(ponto_inicial1);
	Duffing1.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	Duffing1.SetFunction(1, [=](ODEpoint x) { return gamma * cos(1.2 * x.T()) - 0.3 * x.X()[1] + x.X()[0] - pow(x.X()[0], 3); });
	Duffing1.SetTmax(ODE_TMAX);
	vector<ODEpoint> Duffing_sol1=Duffing1.Heun(ODE_STEP);

	vector<double> cond_init2{1.01,0.5};
	ODEpoint ponto_inicial2(0, cond_init2);
	ODEsolver Duffing2(ponto_inicial2);
	Duffing2.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	Duffing2.SetFunction(1, [=](ODEpoint x) { return gamma * cos(1.2 * x.T()) - 0.3 * x.X()[1] + x.X()[0] - pow(x.X()[0], 3); });
	Duffing2.SetTmax(ODE_TMAX);
	vector<ODEpoint> Duffing_sol2=Duffing2.Heun(ODE_STEP);



	vector<double> PhaseSpaceDistance;
	vector<double> Lyaponov;
	double dZ,Ly;
	for (int i = 0; i < Duffing_sol1.size(); ++i) {
		dZ=pow(Duffing_sol1.at(i).X()[0]-Duffing_sol2.at(i).X()[0],2)+pow(Duffing_sol1.at(i).X()[1]-Duffing_sol2.at(i).X()[1],2);
		PhaseSpaceDistance.push_back(dZ);
	}
	for (int i = 1; i < PhaseSpaceDistance.size(); ++i) {
		Ly = log(PhaseSpaceDistance[i]/PhaseSpaceDistance[0])/(Duffing_sol1[i].T());
		Lyaponov.push_back(Ly);
	}

	TApplication app("app", nullptr, nullptr);

	TCanvas *c1 = new TCanvas("c1","X vs. time",200,10,800,500);
	TGraph * points_graph1 = new TGraph();
	TGraph * points_graph2 = new TGraph();

	for (int i = 0; i < Duffing_sol1.size(); ++i) {
		points_graph1->AddPoint(Duffing_sol1.at(i).T(), Duffing_sol1.at(i).X()[0]);
	}
	for (int i = 0; i < Duffing_sol2.size(); ++i) {
		points_graph2->AddPoint(Duffing_sol2.at(i).T(), Duffing_sol2.at(i).X()[0]);
	}
	points_graph1->SetLineColor(2);
	points_graph1->GetXaxis()->SetRangeUser(0.,0.1*ODE_TMAX);
	points_graph1->Draw("AC");
	points_graph2->SetLineColor(4);
	points_graph2->Draw("SAME");

	c1->Update();

	TCanvas *c2 = new TCanvas("c2","Lyaponov Exponent",200,10,800,500);
	TGraph * Lyap_graph = new TGraph();
	for (int i = 0; i < Lyaponov.size(); ++i) {
		Lyap_graph->AddPoint(Duffing_sol1[i].T(),Lyaponov.at(i));
	}
	Lyap_graph->SetLineColor(2);

	Lyap_graph->GetXaxis()->SetRangeUser(0.,ODE_TMAX);
	Lyap_graph->GetYaxis()->SetRangeUser(-1,1);
	Lyap_graph->Draw("AC");
	c2->SetGrid();
	c2->Update();

	TRootCanvas *rc = (TRootCanvas *)c2->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();


	return 0;
}
