#include "../headers/Parameters.h"

#include <random>

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
		// if(this->label == "phi_1"){
		// 	printf("mutate : %f\n", this->value);
		// }
	}
	else{
		rnd = rand() / (double)RAND_MAX;
		change = (MUTATION_RATE/2.) - rnd * MUTATION_RATE;
		this->value *= 1 + change;//+ MUTATION_RATE;
	}
	// if(this->label == "phi_1"){
	// 	printf("phi_1 value = %f\n", this->value);
	// }
}

void Parameters::display(){
	printf("%s : %f < %f < %f\n",this->label.c_str(), this->min, this->value, this->max);
}