//
// Created by pcosme on 13/12/2021.
//

#ifndef NEVILLEINTERPOLATION_H
#define NEVILLEINTERPOLATION_H

#include "DataPoints.h"
#include "Interpolator.h"


using namespace std;

class NevilleInterpolation : public Interpolator{
public:
	explicit NevilleInterpolation(DataPoints dados): Interpolator(dados){};
	~NevilleInterpolation()=default;
	void Interpolate() override;
	double Polynomial(double *x, double *par) override;
};


#endif //NEVILLEINTERPOLATION_H
