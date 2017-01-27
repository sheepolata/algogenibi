#include "../headers/ProtoEye.h"
#include <math.h> //For M_PI
#include <map>
#include <stdio.h>
#include <iostream>

bool apeutpresegal(double d, double d2, double prec){
	return abs(d-d2) < prec;
}

std::map<double, double>* dico = new std::map<double, double>();

ProtoEye::ProtoEye(){
	this->rho_c	= new Parameters(10000., W/2., 10000., "rho_c");
	this->i 	= new Parameters(0., 0., W/2., "i");
	this->phi_1	= new Parameters(0., 0., M_PI/2., "phi_1"); //Mute que quand rho_c == W/2 à epsilon près
	this->n0	= new Parameters(1.35, 1.35, 1.55, "n0");
}

ProtoEye::~ProtoEye(){
	
}

bool ProtoEye::isValid(){
	return this->rho_c->isValid() 
			&& this->i->isValid()
			&& this->phi_1->isValid()
			&& this->n0->isValid();
}


double ProtoEye::p(){
	if(this->rho_c->getValue() > (W/2.)){
		return this->rho_c->getValue() - sqrt(this->rho_c->getValue()*this->rho_c->getValue() - ((W*W)/4));
	}
	else if(this->rho_c->getValue() == (W/2.)){
		return (W/2) * (1 + sin(this->phi_1->getValue()));
	}
	return -1;
}

double ProtoEye::a(){
	if(this->rho_c->getValue() > (W/2)){
		return W - 2 * this->i->getValue(); 
	}
	else if(this->rho_c->getValue() == (W/2)){
		return W * cos(this->phi_1->getValue()) - 2 * this->i->getValue();
	}
	return -1;
}

double ProtoEye::r1(){
	// printf("brefore %f -> ", this->n0->getValue());
	double v = roundf(this->n0->getValue() * 1000) / 1000;
	// printf("after %f\n", this->n0->getValue());
	// printf("dico->at(%f)\n", v);
	return dico->at(v);
}

double ProtoEye::teta(){
	if(this->n0->getValue() == 1.35){
		return 2 * atan(this->a() / (this->p() * 2));
	}
	else if(this->n0->getValue() > 1.35){
		double x		= ((this->r1()*this->r1()) * this->a()) / (2*this->p());
		double y		= 1 + (this->r1()*this->r1()) - (((this->r1()*this->r1()) * (this->a()*this->a())) / (4*(this->p()*this->p())));
		double denom	= x - sqrt(y);
		return 2*asin(denom / (1 + (this->r1()*this->r1())));
	}
	return -1;
}

bool ProtoEye::isDead(){
	if(!this->isValid()){
		// printf("%s\n", "Not all param are valid");
		return true;
	}
	//TODO REGLER PROBLEME PHI_1 
	// bool d1 = this->phi_1->getValue() != 0 && this->rho_c->getValue() != (W/2);
	bool d1 = !apeutpresegal(this->phi_1->getValue(), 0, PRECISION) && !apeutpresegal(this->rho_c->getValue(), (W/2), PRECISION);
	bool d2 = this->phi_1->getValue() != 0 && this->i->getValue() > (W * (cos(this->phi_1->getValue()) / 2));
	// bool d2 = !apeutpresegal(this->phi_1->getValue(), 0, PRECISION) && this->i->getValue() > (W * (cos(this->phi_1->getValue()) / 2));
	bool d3 = this->n0->getValue() != 1.35 && (this->p() > (this->r1() * this->a() / 2) || this->p() < this->a()/2 );
	// bool d3 = !apeutpresegal(this->n0->getValue(), 1.35, PRECISION) && (this->p() > (this->r1() * this->a() / 2) || this->p() < this->a()/2 );
	double tmp = sqrt(exp(1) / (0.746 * sqrt(this->i->getValue())));
	bool d4 = this->n0->getValue() == 1.35 && this->phi_1->getValue() == 0 && this->i->getValue() > 0.5*(W - tmp);
	bool d5 = this->n0->getValue() == 1.35 && this->phi_1->getValue() != 0 && this->i->getValue() > 0.5*(W*cos(this->phi_1->getValue()) - tmp);
	if(d1){
		// if(phi_1->getValue() != 0)
		// 	printf("OMG d1\n");
		return true;
	}
	if(d2){
		// if(phi_1->getValue() != 0)
		// 	printf("OMG d2\n");
		return true;
	}
	if(d3){
		// if(phi_1->getValue() != 0)
		// 	printf("OMG d3\n");
		return true;
	}
	// if(d4){
	// 	// printf("OMG d3\n");
	// 	return true;
	// }
	// if(d5){
	// 	// printf("OMG d3\n");
	// 	return true;
	// }

	return false;
}

double ProtoEye::v(){
	if(this->n0->getValue() == 1.35){
		double root = sqrt(log(0.746 * (this->a()*this->a()) * sqrt(I)));
		return 0.375 * (this->p() / this->a()) * root;
	}
	else if(this->n0->getValue() > 1.35){
		return 1 / this->teta();
	}
	return -1;
}

ProtoEye* breed(ProtoEye const & p1, ProtoEye const & p2){
	//Crossover
	int cross = rand() % 100; //0-99
	ProtoEye* child = new ProtoEye();
	if(cross < CROSSOVER_RATE*100){
		int rnd = rand() % 100;//0-99
		if(rnd < 50)
			child->rho_c->setValue(p1.rho_c->getValue());
		else
			child->rho_c->setValue(p2.rho_c->getValue());
		rnd = rand() % 100;//0-99
		if(rnd < 50)
			child->i->setValue(p1.i->getValue());
		else
			child->i->setValue(p2.i->getValue());
		rnd = rand() % 100;//0-99
		if(rnd < 50)
			child->phi_1->setValue(p1.phi_1->getValue());
		else
			child->phi_1->setValue(p2.phi_1->getValue());
		rnd = rand() % 100;//0-99
		if(rnd < 50)
			child->n0->setValue(p1.n0->getValue());
		else
			child->n0->setValue(p2.n0->getValue());
	}
	else{
		int rnd = rand() % 100;//0-99
		if(rnd < 50){
			child->rho_c->setValue(p1.rho_c->getValue());
			child->i->setValue(p1.i->getValue());
			child->phi_1->setValue(p1.phi_1->getValue());
			child->n0->setValue(p1.n0->getValue());
		}
		else{
			child->rho_c->setValue(p2.rho_c->getValue());
			child->i->setValue(p2.i->getValue());
			child->phi_1->setValue(p2.phi_1->getValue());
			child->n0->setValue(p2.n0->getValue());
		}
	}

	//Mutation
	int rnd = rand() % 100;//0-99
	int cmp = MUTATION_CHANCE*100;
	if(rnd < cmp){
		child->rho_c->mutate();
	}
	rnd = rand() % 100;//0-99
	if(rnd < cmp){
		child->i->mutate();
	}
	rnd = rand() % 100;//0-99
	if(apeutpresegal(child->rho_c->getValue(), W/2, PRECISION) && rnd < cmp){
		// printf("Phi 1 mutate\n");
		child->phi_1->mutate();
		// printf("new val = %f\n", child->phi_1->getValue());
	}
	rnd = rand() % 100;//0-99
	if(rnd < cmp){
		child->n0->mutate();
	}
	return child;
}


void ProtoEye::display(){
	this->rho_c->display();
	this->i->display();
	this->phi_1->display();
	this->n0->display();

	std::cout << "p = " << this->p() << std::endl;
	std::cout << "a = " << this->a() << std::endl;
	std::cout << "r1 = " << this->r1() << std::endl;
	std::cout << "teta = " << this->teta() << std::endl;
}

std::string ProtoEye::to_tsv_line(){
	//Format : rho_c \t i \t phi_1 \t n0 \t p \t a \t r1 \t teta
	std::string res = "";
	res += std::to_string(this->rho_c->getValue());
	res += "\t";
	res += std::to_string(this->i->getValue());
	res += "\t";
	res += std::to_string(this->phi_1->getValue());
	res += "\t";
	res += std::to_string(this->n0->getValue());
	res += "\t";
	res += std::to_string(this->p());
	res += "\t";
	res += std::to_string(this->a());
	res += "\t";
	res += std::to_string(this->r1());
	res += "\t";
	res += std::to_string(this->teta());
	return res;
}

