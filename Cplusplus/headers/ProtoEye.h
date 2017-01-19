#ifndef _PROTOEYE_H
#define _PROTOEYE_H

#include <map>
#include "Parameters.h"

extern std::map<double, double>* dico;

class ProtoEye
{
public:
	ProtoEye();
	~ProtoEye();
	
	bool isValid();

	//Algorithm Functions
	double p();
	double a();
	double r1();
	double teta();

	bool isDead();

	double v();

	friend ProtoEye* breed(ProtoEye const &, ProtoEye const &);

private:
	Parameters* rho_c;
	Parameters* i;
	Parameters* phi_1;
	Parameters* n0;
};
#endif
