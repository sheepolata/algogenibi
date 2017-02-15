#include "../headers/Parameters.h"

#include <random>

bool apeutpresegal(double d, double d2, double prec){
	return abs(d-d2) < prec;
}

Parameters::Parameters(double val, double mini, double maxi, std::string l) : value(val), min(mini), max(maxi), label(l){

}

Parameters::~Parameters(){

}

double Parameters::getValue(){
	return this->value;
}
void Parameters::setValue(double v){
	this->value = v;
}
double Parameters::getMin(){
	return this->min;
}
double Parameters::getMax(){
	return this->max;
}

bool Parameters::isValid(){
	return this->value <= this->max && this->value >= this->min;
}

void Parameters::mutate(){
	double change;
	double rnd;
	if(this->value == 0){
	    change = this->max * MUTATION_RATE;
	    this->value += change;
	}
	else{
		rnd = rand() / (double)RAND_MAX;
		change = (MUTATION_RATE/2.) - rnd * MUTATION_RATE;
		// this->value += (this->max * change);
		this->value *= 1 + change;
	}
}

void Parameters::display(){
	printf("%s : %f < %f < %f\n",this->label.c_str(), this->min, this->value, this->max);
}