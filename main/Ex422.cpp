#include <utility>
#include <iostream>
#include <vector>

#include "../src/DataPoints.h"
#include "../src/LagrangeInterpolation.h"
#include "../src/NevilleInterpolation.h"
#include "../src/HermiteSpline.h"
#include "../src/Spline3Interpolation.h"

using namespace std;

int main() {

	vector<double> x={-1.2,-1,-0.5,-0.3,0.3,0.6,1.1};
	vector<double> y={-5.76,0.1,-4,-3,-5.61,4,-3.69};

//	vector<double> x={-1.2,0.3,1.1};
//	vector<double> y={-5.76,-5.61,-3.69};


	DataPoints Dados(x,y);

	//Dados.PrintPoints();

	vector< pair<double,double> > output;

	output = Dados.GetPoints();

/*
	cout <<"INTERPOLAÇAO DE LAGRANGE "<<endl;
	LagrangeInterpolation Lagrange(Dados);
	Lagrange.PrintPoints();
	Lagrange.Interpolate();
	double X[]={0.0},par[]={0.0};
	cout <<"Valor em x=0\t" << Lagrange.Polynomial(X,par) <<endl;
	Lagrange.Draw();
*/

/*
	cout <<"INTERPOLAÇAO DE NEVILLE "<<endl;
	NevilleInterpolation Neville(Dados);
	Neville.PrintPoints();
	Neville.Interpolate();
	Neville.Draw();
*/

/*
	cout <<"INTERPOLAÇAO DE HERMITE "<<endl;
	HermiteSpline Hermite(Dados);
	Hermite.PrintPoints();
	Hermite.Interpolate();
	Hermite.Draw();
*/

	cout <<"INTERPOLAÇAO SPLINE CUBICO "<<endl;
	Spline3 Spline(Dados);
	Spline.PrintPoints();
	Spline.Interpolate();
	Spline.Draw();

	return 0;
}