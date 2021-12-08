#include <utility>
#include <iostream>

#include "../src/Material.h"
#include "../src/OpticalMat.h"

using namespace std;

int main() {

	string nome;
	nome = "diamond";
	Double_t densidade=3.35;

	vector<pair<float, float> > refindex = { {687.7, 2.40735}, {589.3,2.41734}, {527.0,2.42694} , {396.8,2.46476} };


	OpticalMat Diamond(nome,densidade);

	Diamond.SetRefIndex(refindex);
	Diamond.Print();
	Diamond.FitDataPoints();
	vector<double> parametros;
	vector<double> erro_parametros;
	double chiquadrado=0;
	Diamond.GetFitResults(parametros,erro_parametros,chiquadrado);
	Diamond.DrawFitRefIndex();
}


