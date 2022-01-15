//
// Created by pcosme on 14/01/2022.
//

#ifndef ODEPOINT_H
#define ODEPOINT_H

#include <utility>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Xvar {
public:
	Xvar() = default;
	~Xvar() = default;

	explicit Xvar(const std::vector<double>& v_in);
	Xvar(const Xvar&); // copy constructor

	Xvar& operator=(const Xvar&);
	vector<double>& X(); // accessor to x
protected:
	vector<double> x;
};


class ODEpoint : public Xvar{
private:
	double t; // time
public:
	ODEpoint() : t(0) {;}
	ODEpoint(double t_in, const Xvar& a_in) : Xvar(a_in), t(t_in) {;}
	ODEpoint(double t_in, const vector<double>& v_in) : Xvar(v_in), t(t_in) {;}

	ODEpoint& operator=(const ODEpoint&); // assignment operator

	void SetODEpoint(double t_in, Xvar& a_in);
	void SetODEpoint(double t_in, vector<double> v_in);

	double& T() { return t;} // accessor to time

};


#endif //ODEPOINT_H
