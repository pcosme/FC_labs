//
// Created by pcosme on 13/12/2021.
//

#include "DataPoints.h"


DataPoints::DataPoints(const vector<double> &x, const vector<double> &y) {
	for (int i = 0; i < x.size(); i++){
		P.push_back( make_pair( x[i], y[i] ) );
	}
}

void DataPoints::PrintPoints() const{
	for(auto itr=P.begin(); itr !=P.end(); itr++){
		cout << itr->first <<"\t"<< itr->second <<endl;
	}
}

const vector<pair<double, double> > & DataPoints::GetPoints() const{
	return P;
}
