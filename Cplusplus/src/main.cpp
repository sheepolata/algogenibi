#include <stdio.h>
#include <time.h>
#include <fstream>	
#include <iostream>
#include <string.h>
#include <vector>

#include <iomanip>
#include <ctime>
#include <chrono>

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

unsigned int max_index(double* tab, int size){
	unsigned int i = 0;
	double tmp = -1000000;
	for (int j = 0; j < size; j++)
	{
		if(tab[j] > tmp){
			i = j;
			tmp = tab[j];
		}
	}
	return i;
}

int get_parent_index(double* repartition){
	double rnd = rand() / (double) RAND_MAX;
	int cmp = 0;
	while(rnd > repartition[cmp]){
		cmp++;
	}
	return cmp;
}

std::string CurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", std::localtime(&now));
    return buf;
}

int main(int argc, char const *argv[])
{
	/* initialize random seed: */
	srand(time(NULL));
	printf("seed = %ld\n", time(NULL));

	load_tsv();

    // std::string time = get_date_string(std::system_clock::now());
    std::string time = CurrentDate();

	std::ofstream outfile;
  	outfile.open ("./results/"+time+"_results.tsv");
  	std::string entete = "";
  	entete += "rho_c\ti\tphi_1\tn0\tp\ta\tr1\tteta";
  	outfile << entete << "\n";

	std::vector<ProtoEye *>* pop = new std::vector<ProtoEye *>();
	for (int i = 0; i < POP_SIZE; i++) {
		pop->push_back(new ProtoEye());
	}

	for (int gen = 0; gen < NB_GEN; gen++)
	{
		if(gen%(NB_GEN/10) == 0){
			printf("---- Generation %d ----\n", gen);
		}
		double* fitness 	= new double[POP_SIZE];
		double* proba 		= new double[POP_SIZE];
		double* repartition = new double[POP_SIZE];
		double sum 			= 0;
		unsigned int 		i_best;
		for (unsigned int fi = 0; fi < pop->size(); fi++)
		{
			fitness[fi] = pop->at(fi)->v() * 1000;
			sum += fitness[fi];
		}
		i_best = max_index(fitness, POP_SIZE);
		if(gen%(NB_GEN/10) == 0){
			// pop->at(i_best)->display();
			std::cout << pop->at(i_best)->to_tsv_line() <<std::endl;
		}
		outfile << pop->at(i_best)->to_tsv_line() << "\n";
		for (unsigned int fi = 0; fi < pop->size(); fi++)
		{
			proba[fi] = fitness[fi] / sum;
		}
		repartition[0] = proba[0];
		for (unsigned int fi = 1; fi < pop->size(); fi++)
		{
			repartition[fi] = repartition[fi-1] + proba[fi];
		}

		std::vector<ProtoEye *>* new_pop = new std::vector<ProtoEye *>();
		while(new_pop->size() < POP_SIZE/*false*/){
			//Pick parents
			int pi1 = get_parent_index(repartition);
			int pi2;
			int timeout = 0;
			do{
				pi2 = get_parent_index(repartition);
				timeout++;
			}while(pi1 == pi2 && timeout < 5000);
			ProtoEye * p1 = pop->at(pi1);
			ProtoEye * p2 = pop->at(pi2);


			//Breed
			ProtoEye * child;
			child = breed(*p1, *p2);
			// if(gen%1500 == 0){
			// 	printf("child phi1 = %f\n", child->phi_1->getValue());
			// 	printf("child rho_c = %f\n", child->rho_c->getValue());
			// 	printf("child i = %f\n", child->i->getValue());
			// 	printf("child n0 = %f\n\n", child->n0->getValue());
			// }
			// printf("n0 = %f\n", child->n0->getValue());
			//Check if child OK
			//If OK, add child to new pop
			//Else, repeat from pick parent
			if(!child->isDead()){
				new_pop->push_back(child);
			}
			else{
				delete child;
			}
		}

		//Set pop = new_pop
		delete pop;
		pop = new_pop;

		//Clean memory TODO
		delete fitness;
		delete proba;
	}
	outfile.close();

	delete pop;
	return 0;
}	