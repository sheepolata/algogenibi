#include "../headers/ProtoEye.h"
#include <math.h> //For M_PI

ProtoEye::ProtoEye(){
	this->rho_c	= new Parameters(10000.f, W/2.f, 10000.f);
	this->i 	= new Parameters(0.f, 0.f, W/2.f);
	this->phi_1	= new Parameters(0.f, 0.f, M_PI/2.f);
	this->n0	= new Parameters(1.35f, 1.35f, 1.55f);
}

ProtoEye::~ProtoEye(){
	
}