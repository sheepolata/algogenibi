#include <stdio.h>
#include <time.h>
#include <fstream>	
#include <iostream>
#include <string.h>
#include <vector>

#include "../headers/Parameters.h"
#include "../headers/ProtoEye.h"


void load_tsv(){
	std::ifstream fichier("../indice_refraction_facile.dat", std::ios::in);  // on ouvre le fichier en lecture
 
    if(fichier)  // si l'ouverture a réussi
    {
    	std::string line;
    	std::getline(fichier, line);
        while(std::getline(fichier, line))  // tant que l'on peut mettre la line dans "contenu"
        {
        	char* tmp = new char[line.length() + 1];
        	strcpy(tmp, line.c_str());
        	char* r1 = strtok(tmp, "\t");
        	char* vitrious = strtok(NULL, "\t");
            dico->insert ( std::pair<float, float>(std::stof(vitrious), std::stof(r1) ));
        }
        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}

int main(int argc, char const *argv[])
{
	/* initialize random seed: */
	srand(time(NULL));
	printf("seed = %ld\n", time(NULL));

	load_tsv();

	std::vector<ProtoEye *>* pop = new std::vector<ProtoEye *>();
	for (int i = 0; i < POP_SIZE; i++) {
		pop->push_back(new ProtoEye());
	}

	for (int gen = 0; gen < NB_GEN; gen++)
	{
		printf("Generation %d\n", gen);
		double* fitness = new double[POP_SIZE];
		double sum = 0;
		for (unsigned int fi = 0; fi < pop->size(); fi++)
		{
			fitness[fi] = pop->at(fi)->v() * 1000;
			sum += fitness[fi];
		}
		

		std::vector<ProtoEye *>* new_pop = new std::vector<ProtoEye *>();
		while(new_pop.size() < POP_SIZE){
			//Pick parents
			ProtoEye * p1;
			ProtoEye * p2;

			//Breed
			ProtoEye * child;
			//child = breed(*p1, *p2);

			//Check if child OK
			//If OK, add child to new pop
			//Else, repeat from pick parent
		}

		//Set pop = new_pop
	}


	// ProtoEye* pe = new ProtoEye();
	// ProtoEye* pe2 = new ProtoEye();

	// std::cout << "pe" << std::endl;
	// std::cout << pe->p() << std::endl;
	// std::cout << pe->a() << std::endl;
	// std::cout << pe->r1() << std::endl;
	// std::cout << pe->teta() << std::endl;
	// std::cout << pe->isDead() << std::endl;

	// std::cout << "pe2" << std::endl;
	// std::cout << pe2->p() << std::endl;
	// std::cout << pe2->a() << std::endl;
	// std::cout << pe2->r1() << std::endl;
	// std::cout << pe2->teta() << std::endl;
	// std::cout << pe2->isDead() << std::endl;

	// ProtoEye* c = breed(*pe, *pe2);

	// std::cout << "c" << std::endl;
	// std::cout << c->p() << std::endl;
	// std::cout << c->a() << std::endl;
	// std::cout << c->r1() << std::endl;
	// std::cout << c->teta() << std::endl;
	// std::cout << c->isDead() << std::endl;

	// delete p;
	return 0;
}	