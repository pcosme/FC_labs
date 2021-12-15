//
// Created by pcosme on 13/12/2021.
//

#include "LagrangeInterpolation.h"

void LagrangeInterpolation::Interpolate() {
	float Xmin=point_x[0];
	float Xmax=point_x[this->GetNumberofPoints()-1];
	interpol_polynomial = new TF1("InterpolatorPolynomial", this, &LagrangeInterpolation::Polynomial, Xmin, Xmax, 0);
}

double LagrangeInterpolation::Polynomial(double *x, double *par) {
	int k = this->GetNumberofPoints();
	double L=0;
	for (int i = 0; i < k; ++i) {
		double l=1.0;
		for (int j = 0; j < k; ++j) {
			if (j!=i){
				l *= (x[0]-point_x[j])/(point_x[i]-point_x[j]);
			}
		}
		L += point_y[i]*l;
	}
	return L;
}
