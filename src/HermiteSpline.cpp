//
// Created by pcosme on 14/12/2021.
//

#include "HermiteSpline.h"

double HermiteSpline::h00(double t) {
	return 2*t*t*t-3*t*t+1;
}
double HermiteSpline::h10(double t) {
	return t*t*t-2*t*t+t;
}
double HermiteSpline::h01(double t) {
	return -2*t*t*t+3*t*t;
}
double HermiteSpline::h11(double t) {
	return t*t*t-t*t;
}

unsigned int HermiteSpline::FindInterval(double x) {
	int n=this->GetNumberofPoints();
	int left_index=0;
	for (int i = 0; i < n-1; ++i) {
		if(point_x[i] <= x && x < point_x[i+1] ){
			left_index=i;
		}
	}
	return left_index;
}

double HermiteSpline::Polynomial(double *x, double *par) {
	int n = this->GetNumberofPoints();
	int k = this->FindInterval(x[0]);
	double t = (x[0] - point_x[k])/(point_x[k+1] - point_x[k]);


	M.resize(n);
	M[0]   = (point_y[1] - point_y[0]) / (point_x[1] - point_x[0]);
	M[n - 1] = (point_y[n - 1] - point_y[n - 2]) / (point_x[n - 1] - point_x[n - 2]);
	for (int i = 2; i < n-1; ++i) {
		M[i] = 0.5 * ((point_y[i + 1] - point_y[i]) / (point_x[i + 1] - point_x[i]) +
				     (point_y[i]-point_y[i-1])/(point_x[i]-point_x[i-1]) );
	}

	return h00(t)*point_y[k] + h10(t) * (point_x[k+1]-point_x[k]) * M[k] + h01(t) * point_y[k + 1] + h11(t) * (point_x[k + 1] - point_x[k]) * M[k + 1];
}

void HermiteSpline::Interpolate() {
	float Xmin=point_x[0];
	float Xmax=point_x[this->GetNumberofPoints()-1];
	interpol_polynomial = new TF1("InterpolatorPolynomial", this, &HermiteSpline::Polynomial, Xmin, Xmax, 0);
}