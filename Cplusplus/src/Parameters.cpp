#include "../headers/Parameters.h"

Parameters::Parameters(float val, float mini, float maxi) : value(val), min(mini), max(maxi){

}

Parameters::~Parameters(){

}

float Parameters::getValue(){
	return this->value;
}
float Parameters::getMin(){
	return this->min;
}
float Parameters::getMax(){
	return this->max;
}

bool Parameters::isValid(){
	return this->value < this->max && this->value > this->min;
}

void Parameters::mutate(){
	float change;
	float rnd;
	rnd = rand() / (float)RAND_MAX;
	change = (MUTATION_RATE/2.f) - rnd * MUTATION_RATE;
	this->value *= 1 + change;
}

void Parameters::display(){
	printf("%f < %f < %f\n", this->min, this->value, this->max);
}