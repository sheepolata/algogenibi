#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double W = 1.5;//cm, largeur max de l'oeil
const double I = exp(6); //Intensite lumineuse

const double CROSSOVER_RATE 	= 0.20;
const double MUTATION_RATE 	= 0.01;
const double MUTATION_CHANCE = 0.05; //5-25%
const double PRECISION		= 0.0001;
const int POP_SIZE			= 10;
const int NB_GEN			= 10;

class Parameters
{
public:
	Parameters(double, double, double);
	~Parameters();

	double getValue();
	void setValue(double);
	double getMin();
	double getMax();

	bool isValid();

	void mutate();

	void display();
	//TODO
	/*bool operator==(const Parameters& o){
		return this->value == o.value && this->min == o.min && this->max == o.max;
	}
	bool operator!=(const Parameters& o){
		return !(*this == o);
	}*/

private:
	double value;
	double min;
	double max;
};

#endif
