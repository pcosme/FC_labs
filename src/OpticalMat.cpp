
#include "OpticalMat.h"


OpticalMat::OpticalMat(string name,Double_t density) : Material(name,density){
	fit_function = new TF1("FitDataPoints", OpticalMat::FitRefIndex, 380, 700, 5);
	fit_function->SetParameters(2.4,1,1,0.1,0.1);
}


OpticalMat::~OpticalMat() = default;


void OpticalMat::SetRefIndex(vector<pair<float, float>> input_list) {
	refractive_index_list=input_list;
	for(auto itr=refractive_index_list.begin(); itr !=refractive_index_list.end(); itr++){
		ref_index_points_graph->AddPoint(itr->first, itr->second);
	}
}

void OpticalMat::Print() {
	Material::Print();
	cout<<"\nwavelength [nm]"<<"\t"<<"refractive index"<<endl;
	for(auto itr=refractive_index_list.begin(); itr !=refractive_index_list.end(); itr++){
		cout<<itr->first<<"\t"<<itr->second<<endl;
	}
}


double OpticalMat::FitRefIndex(double* x, double* par){
	return par[0]+par[1]/(x[0]*x[0]-0.028)+par[2]/pow(x[0]*x[0]-0.028,2)+par[3]*x[0]*x[0]+par[4]*pow(x[0],4);
}

void OpticalMat::GetFitResults(vector<double>& param, vector<double>& paramerror, double& chisqr) {
	chisqr = fit_results_pointer->Chi2();
	int ndf=fit_results_pointer->Ndf();

	//float adjust=sqrt(chisqr/( (ndf>1)?ndf-1:1 ) );
	float adjust =1.0f;

	const double *err= fit_results_pointer->GetErrors();
	const double *par= fit_results_pointer->GetParams();

	for(unsigned int i=0;i<fit_results_pointer->NPar();i++){
		param.push_back(par[i]);
		paramerror.push_back(err[i]/adjust);
	}

}

void OpticalMat::FitDataPoints() {
	fit_results_pointer = ref_index_points_graph->Fit("FitDataPoints", "S", "", 380, 700);
}



void OpticalMat::DrawFitRefIndex() {
	TApplication app("app", nullptr, nullptr);
	TCanvas *c1 = new TCanvas("c1","Refractive index points",200,10,800,500);

	this->FitDataPoints();

	ref_index_points_graph->SetTitle("Refractive index");
	ref_index_points_graph->GetYaxis()->SetTitle("n");
	ref_index_points_graph->GetXaxis()->SetTitle("wavelength [nm]");
	ref_index_points_graph->Draw("A*");
	c1->Update();

	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	app.Run();
}

void OpticalMat::DrawRefIndexPoints() {
	TApplication app("app", nullptr, nullptr);
	TCanvas *c1 = new TCanvas("c1","Refractive index points",200,10,800,500);
	ref_index_points_graph->SetTitle("Refractive index");
	ref_index_points_graph->GetYaxis()->SetTitle("n");
	ref_index_points_graph->GetXaxis()->SetTitle("wavelength [nm]");
	ref_index_points_graph->Draw("A*");
	c1->Update();

	TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

	app.Run();
}
/*
TF1 *OpticalMat::GetFitRefIndex() {
	return nullptr;
}

void OpticalMat::SetFitRefIndex(TF1 * input_fit_function) {
	fit_function=input_fit_function;
}

vector<pair<float, float> > OpticalMat::GetRefIndex() {
	return vector<pair<float, float>>();
}
*/