//
// Created by pcosme on 13/12/2021.
//

#ifndef DATAPOINTS_H
#define DATAPOINTS_H

#include <utility>
#include <iostream>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"

#include "TRootCanvas.h"
#include "TApplication.h"


using namespace std;

class DataPoints {
public:
//	DataPoints(int N, double* x, double* y); // build DataPoints from C-arrays of x and y values
//	DataPoints(const vector< pair<double,double> >&);
	DataPoints(const vector< double>& x, const vector< double>& y);
	~DataPoints() = default;
// getters
	const vector< pair<double,double> >& GetPoints() const;
	void PrintPoints() const;
//	void GetGraph(TGraph&);
// draw points using ROOT object TGraph
//	void Draw();

protected:
	vector< pair<double,double> > P; // points
};


#endif //DATAPOINTS_H
