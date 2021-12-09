

#ifndef OPTICALMAT_H
#define OPTICALMAT_H

#include <utility>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TF1.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TRootCanvas.h"
#include "TApplication.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "Material.h"


using namespace std;

class OpticalMat : public Material  {
public:
	OpticalMat(string name, Double_t density);
	~OpticalMat();

	void SetRefIndex(vector<pair<float,float> >); //pair(wavelength, ref index)
	//vector<pair<float,float> > GetRefIndex();
	//void SetFitRefIndex(TF1*); //provide function to be fitted through TF1
	//TF1* GetFitRefIndex(); //return TF1 pointer to fit function
	void DrawRefIndexPoints(); //draw points
	void DrawFitRefIndex(); //draw points and function
	void Print() override; //define print for this class

	void GetFitResults(vector<double> &param, vector<double> &paramerror, double& chisqr);
	void FitDataPoints();
private:

	vector<pair<float,float> > refractive_index_list;
	static double FitRefIndex(double* x, double* par);
	TF1* fit_function ;
	TGraph * ref_index_points_graph = new TGraph();
	TFitResultPtr fit_results_pointer;
};


#endif //OPTICALMAT_H
