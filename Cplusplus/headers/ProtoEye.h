#ifndef _PROTOEYE_H
#define _PROTOEYE_H

#include "Parameters.h"


class ProtoEye
{
public:
	ProtoEye();
	~ProtoEye();
	

private:
	Parameters* rho_c;
	Parameters* i;
	Parameters* phi_1;
	Parameters* n0;
};


#endif
