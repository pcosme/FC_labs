//
// Created by pcosme on 14/12/2021.
//

#ifndef HERMITESPLINE_H
#define HERMITESPLINE_H

#include "DataPoints.h"
#include "Interpolator.h"

using namespace std;

class HermiteSpline : public Interpolator {
public:
	explicit HermiteSpline(DataPoints dados): Interpolator(dados){};
	~HermiteSpline()=default;
	void Interpolate() override;
	double Polynomial(double *x, double *par) override;
private:
	vector<double> M;
	unsigned int FindInterval(double x);
	double h00(double t);
	double h10(double t);
	double h01(double t);
	double h11(double t);
};


#endif //HERMITESPLINE_H
