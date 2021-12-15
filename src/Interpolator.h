//
// Created by pcosme on 13/12/2021.
//

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <utility>
#include <iostream>
#include <vector>
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "TRootCanvas.h"
#include "TApplication.h"

#include "DataPoints.h"

using namespace std;

class Interpolator {
public:
	explicit Interpolator(DataPoints data_points);
	~Interpolator()=default;
	virtual void Interpolate() = 0;
	virtual double Polynomial(double *x, double *par) = 0;
	void Draw();
	void PrintPoints();
	int GetNumberofPoints() const ;
protected:
	vector<double> point_x;
	vector<double> point_y;
	TF1* interpol_polynomial;
};


#endif //INTERPOLATOR_H
