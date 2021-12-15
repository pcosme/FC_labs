//
// Created by pcosme on 13/12/2021.
//

#include "NevilleInterpolation.h"

double NevilleInterpolation::Polynomial(double *x, double *par) {
	const int n =this->GetNumberofPoints();
	vector<vector<double>> P(n, vector<double> (n, 0));

	for (int i = 0; i < n; i++){
		P[i][0]=point_y[i];
	}

	for(int i = 1; i < n; i++)
	{
		for(int j = i; j < n; j++)
		{
			P[j][i] = ((x[0] - point_x[j-i]) * P[j][i-1] - (x[0] - point_x[j]) * P[j-1][i-1]) / (point_x[j] - point_x[j-i]);
		}
	}
	return P[n-1][n-1];
}


void NevilleInterpolation::Interpolate() {
	float Xmin=point_x[0];
	float Xmax=point_x[this->GetNumberofPoints()-1];
	interpol_polynomial = new TF1("InterpolatorPolynomial", this, &NevilleInterpolation::Polynomial, Xmin, Xmax, 0);
}
