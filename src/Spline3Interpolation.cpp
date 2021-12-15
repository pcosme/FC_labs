//
// Created by pcosme on 13/12/2021.
//

#include "Spline3Interpolation.h"

using namespace Eigen;
void Spline3::Interpolate() {
	float Xmin=point_x[0];
	float Xmax=point_x[this->GetNumberofPoints()-1];
	interpol_polynomial = new TF1("InterpolatorPolynomial", this, &Spline3::Polynomial, Xmin, Xmax, 0);
}

double Spline3::Polynomial(double *x, double *par) {
	int n = this->GetNumberofPoints();
	int k = this->FindInterval(x[0]);

	this->SolveSystem();

	double deltaX=point_x[k]-point_x[k+1];
	return 0.5*K[k]  *( pow(x[0]-point_x[k+1],2)/deltaX-deltaX/3.0)
	     - 0.5*K[k+1]*( pow(x[0]-point_x[k],2)/deltaX-deltaX/3.0)
		 +(point_y[k]-point_y[k+1])/deltaX;
}

void Spline3::SolveSystem() {
	int n = this->GetNumberofPoints();

	Eigen::Matrix<double,Eigen::Dynamic,1> shortK;
	Eigen::Matrix<double,Eigen::Dynamic,1> B;
	Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A;

	shortK.resize(n-2,1);
	A.resize(n-2,n-2);
	B.resize(n-2, 1);
	A.setZero();

	/**RESOLVER O SISTEMA AQUI**/

	for (int i = 0; i < n-2; ++i) {
		K[i+1] = shortK[i];
	}
	K[0]=0.0;
	K[n-1]=0.0;
}
