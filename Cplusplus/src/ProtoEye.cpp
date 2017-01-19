#include "../headers/ProtoEye.h"
#include <math.h> //For M_PI
#include <map>

std::map<float, float>* dico = new std::map<float, float>();


ProtoEye::ProtoEye(){
	this->rho_c	= new Parameters(10000.f, W/2.f, 10000.f);
	this->i 	= new Parameters(0.f, 0.f, W/2.f);
	this->phi_1	= new Parameters(0.f, 0.f, M_PI/2.f);
	this->n0	= new Parameters(1.35f, 1.35f, 1.55f);
}

ProtoEye::~ProtoEye(){
	
}

bool ProtoEye::isValid(){
	return this->rho_c->isValid() 
			&& this->i->isValid()
			&& this->phi_1->isValid()
			&& this->n0->isValid();
}



