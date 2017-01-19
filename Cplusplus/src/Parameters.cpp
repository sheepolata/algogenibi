#include "../headers/Parameters.h"

Parameters::Parameters(double val, double mini, double maxi) : value(val), min(mini), max(maxi){

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
	rnd = rand() / (double)RAND_MAX;
	change = (MUTATION_RATE/2.) - rnd * MUTATION_RATE;
	this->value *= 1 + change;
}

void Parameters::display(){
	printf("%f < %f < %f\n", this->min, this->value, this->max);
}