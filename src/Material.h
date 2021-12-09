
#ifndef MATERIAL_H
#define MATERIAL_H

#include <utility>
#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"

#include "TRootCanvas.h"
#include "TApplication.h"


using namespace std;

class Material {
public:
	Material(string fname="", Double_t fdens=0): name(fname), density(fdens){;}
	~Material()=default;
	string GetName() {return name;}
	Double_t GetDensity() const {return density;}
	virtual void Print();
protected:
	string name;
	Double_t density;
};


#endif //MATERIAL_H
