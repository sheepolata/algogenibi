#ifndef _PROTOEYE_H
#define _PROTOEYE_H

#include <map>
#include "Parameters.h"

extern std::map<float, float>* dico;

class ProtoEye
{
public:
	ProtoEye();
	~ProtoEye();
	
	bool isValid();

	//Algorithm Functions
	float p();
	float a();
	float r1();
	float teta();

private:
	Parameters* rho_c;
	Parameters* i;
	Parameters* phi_1;
	Parameters* n0;
};


#endif
