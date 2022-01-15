//
// Created by pcosme on 14/01/2022.
//

#include "ODEpoint.h"

#include <utility>

Xvar::Xvar(const std::vector<double>& v_in) {
   x=v_in;
}

Xvar::Xvar(const Xvar & a_in) {
	x=a_in.x;
}

Xvar &Xvar::operator=(const Xvar &a_in) {
	if(this != &a_in) {x=a_in.x;}
	return *this;
}




std::vector<double> &Xvar::X() {
	return x;
}



void ODEpoint::SetODEpoint(double t_in, Xvar &a_in) {
	t=t_in;
	x=a_in.X();
}

void ODEpoint::SetODEpoint(double t_in, std::vector<double> v_in) {
	t=t_in;
	x=std::move(v_in);
}

ODEpoint &ODEpoint::operator=(const ODEpoint &a_in) {
	if(this != &a_in) {
		x=a_in.x;
		t=a_in.t;
	}
	return *this;
}
