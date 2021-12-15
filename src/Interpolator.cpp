//
// Created by pcosme on 13/12/2021.
//

#include "Interpolator.h"


Interpolator::Interpolator(DataPoints data_points) {
	vector< pair<double,double> > input;
	input = data_points.GetPoints();
	for(auto itr=input.begin(); itr !=input.end(); itr++){
		point_x.push_back(itr->first);
		point_y.push_back(itr->second);
	}
}

void Interpolator::Draw() {
	TApplication app("app", nullptr, nullptr);
	TCanvas *c1 = new TCanvas("c1","Refractive index points",200,10,800,500);

	TGraph * points_graph = new TGraph();

	for (int i = 0; i < this->GetNumberofPoints(); ++i) {
		points_graph->AddPoint(point_x[i],point_y[i]);
	}

	points_graph->Draw("A*");

	interpol_polynomial->Draw("SAME");

	c1->Update();

	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();
}

void Interpolator::PrintPoints() {
	for (int i = 0; i < point_x.size(); i++){
		cout <<point_x[i] <<"\t"<< point_y[i] <<endl;
	}
}

int Interpolator::GetNumberofPoints() const {
	return point_x.size();
}

