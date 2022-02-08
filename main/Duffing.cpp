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
#define ODE_TMAX 500

int main() {

	double gamma=0.5;
	vector<double> cond_init{1,0};
	ODEpoint ponto_inicial(0, cond_init);
	ODEsolver Duffing(ponto_inicial);
	Duffing.SetFunction(0, [](ODEpoint x) { return x.X()[1]; });
	Duffing.SetFunction(1, [=](ODEpoint x) { return gamma * cos(1.2 * x.T()) - 0.3 * x.X()[1] + x.X()[0] - pow(x.X()[0], 3); });
	Duffing.SetTmax(ODE_TMAX);
	vector<ODEpoint> Duffing_sol=Duffing.Heun(ODE_STEP);
//	Duffing.FileOutput();

	double left;
	double center;
	double right;
	vector<double> maxima;
	vector<double> minima;
	vector<double> pos_maxima;
	vector<double> pos_minima;
	for (int i = 1; i < Duffing_sol.size()-1; ++i) {
		left=Duffing_sol.at(i-1).X()[0];
		center=Duffing_sol.at(i).X()[0];
		right=Duffing_sol.at(i+1).X()[0];
		if(center>=left && center>=right){
			maxima.push_back(center);
			pos_maxima.push_back(Duffing_sol.at(i).T());
		} else
		if(center<=left && center<=right){
			minima.push_back(center);
			pos_minima.push_back(Duffing_sol.at(i).T());
		}
	}

	TApplication app("app", nullptr, nullptr);

	TCanvas *c1 = new TCanvas("c1","X vs. time",200,10,800,500);
	TGraph * points_graph = new TGraph();

	for (int i = 0; i < Duffing_sol.size(); ++i) {
		points_graph->AddPoint(Duffing_sol.at(i).T(),Duffing_sol.at(i).X()[0]);
	}
	points_graph->SetLineColor(2);
	points_graph->Draw("AC");

	TGraph * maxima_graph = new TGraph();
	for (int i = 0; i < maxima.size(); ++i) {
		maxima_graph->AddPoint(pos_maxima.at(i),maxima.at(i));
	}
	maxima_graph->SetMarkerColor(4);
	maxima_graph->Draw("* SAME");

	c1->Update();



	TCanvas *c2 = new TCanvas("c2","Phase Space",200,10,800,500);
	TGraph * points_phase_space = new TGraph();
	for (int i = 0; i < Duffing_sol.size(); ++i) {
		points_phase_space->AddPoint(Duffing_sol.at(i).X()[0],Duffing_sol.at(i).X()[1]);
	}
	points_phase_space->SetLineColor(2);
	points_phase_space->Draw("AC");
	c2->Update();


	TCanvas *c3 = new TCanvas("c3","First Recurrence Map",200,10,500,500);
	TGraph * recur_map = new TGraph();
	for (int i = 0; i < maxima.size()-1; ++i) {
		recur_map->AddPoint(maxima.at(i),maxima.at(i+1));
	}
	recur_map->SetMarkerColor(2);
	recur_map->SetMarkerStyle(2);
	recur_map->Draw("AP");


	c3->Update();



	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();


	return 0;
}
