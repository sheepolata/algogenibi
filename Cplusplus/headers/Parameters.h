#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

const float W = 1.5f;//cm, largeur max de l'oeil
const float I = exp(6); //Intensite lumineuse

const float CROSSOVER_RATE 	= 0.20f;
const float MUTATION_RATE 	= 0.01f;
const float MUTATION_CHANCE = 0.05f;
const float PRECISION		= 0.00001f;
const int POP_SIZE			= 100;
const int NB_GEN			= 100;

class Parameters
{
public:
	Parameters(float, float, float);
	~Parameters();

	float getValue();
	float getMin();
	float getMax();

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
	float value;
	float min;
	float max;
};

#endif
