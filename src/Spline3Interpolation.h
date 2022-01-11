//
// Created by pcosme on 13/12/2021.
//

#ifndef SPLINE3_H
#define SPLINE3_H

#include "DataPoints.h"
#include "Interpolator.h"
#include "HermiteSpline.h"

#include <Eigen/Core>
#include <Eigen/Dense>
using namespace Eigen;

using namespace std;

class Spline3: public Interpolator{
public:
	explicit Spline3(DataPoints dados): Interpolator(dados){};
	~Spline3()=default;
	void Interpolate() override;
	double Polynomial(double *x, double *par) override;
private:
	vector<double> Ksol;
	void SolveSystem();
	unsigned int FindInterval(double x);
};


#endif //SPLINE3_H
