//
// Created by pcosme on 13/12/2021.
//

#ifndef LAGRANGEINTERPOLATION_H
#define LAGRANGEINTERPOLATION_H

#include "DataPoints.h"
#include "Interpolator.h"


using namespace std;


class LagrangeInterpolation : public Interpolator {
public:
	explicit LagrangeInterpolation(DataPoints dados): Interpolator(dados){};
	~LagrangeInterpolation()=default;
	void Interpolate() override;
	double Polynomial(double *x, double *par) override;
};

#endif //LAGRANGEINTERPOLATION_H
