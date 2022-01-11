//
// Created by pcosme on 13/12/2021.
//

#include "Spline3Interpolation.h"

using namespace Eigen;
void Spline3::Interpolate() {
	float Xmin=point_x[0];
	float Xmax=point_x[this->GetNumberofPoints()-1];

	this->SolveSystem();

	interpol_polynomial = new TF1("InterpolatorPolynomial", this, &Spline3::Polynomial, Xmin, Xmax, 0);
}

double Spline3::Polynomial(double *x, double *par) {
//	int n = this->GetNumberofPoints();
	int k = this->FindInterval(x[0]);

//	this->SolveSystem();

	double deltaX=point_x[k]-point_x[k+1];
	return  (Ksol[k]/6.0) * (pow(x[0] - point_x[k + 1], 3) / deltaX - (x[0] - point_x[k + 1])*deltaX )
	     -  (Ksol[k + 1]/6.0) * (pow(x[0] - point_x[k], 3) / deltaX - (x[0] - point_x[k])*deltaX )
		 +(point_y[k]*(x[0] - point_x[k+1])-point_y[k+1]*(x[0] - point_x[k]))/deltaX;
}

void Spline3::SolveSystem() {
	int n = this->GetNumberofPoints();

	Eigen::Matrix<double,Eigen::Dynamic,1> K;
	Eigen::Matrix<double,Eigen::Dynamic,1> B;
	Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A;

	/*Sistem AK=B*/

	K.resize(n,1);
	A.resize(n,n);
	B.resize(n, 1);

	A.setZero();
	for (int row = 1; row < n-1; ++row) {
		for (int col = 1; col < n-1; ++col) {
			if(col==row){
				A(row,col) = 2.0f*(point_x[row-1]-point_x[row+1]);
			}
			if(col==row+1){
				A(row,col) = (point_x[row]-point_x[row+1]);
			}
			if(col==row-1){
				A(row,col) = (point_x[row-1]-point_x[row]);
			}
		}
	}
	A(0,0)=1;
	A(n-1,n-1)=1;

	for (int row = 1; row < n-1; ++row) {
		B(row)= 6.0*((point_y[row-1]-point_y[row])/(point_x[row-1]-point_x[row]) - (point_y[row]-point_y[row+1])/(point_x[row]-point_x[row+1]));
	}
	B(0)=1;
	B(n-1)=1;

	/**RESOLVER O SISTEMA AQUI**/
	K = A.lu().solve(B);

	for (int i = 0; i < n; ++i) { //copiar a soluçao para o Ksol
		Ksol.push_back(K(i));
	}
}
unsigned int Spline3::FindInterval(double x) {
	int n=this->GetNumberofPoints();
	int left_index=0;
	for (int i = 0; i < n-1; ++i) {
		if(point_x[i] <= x && x < point_x[i+1] ){
			left_index=i;
		}
	}
	return left_index;
}