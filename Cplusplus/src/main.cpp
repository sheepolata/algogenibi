#include <stdio.h>
#include <time.h>
#include <fstream>	
#include <iostream>
#include <string.h>
#include <vector>

#include <iomanip>
#include <ctime>
#include <chrono>

#include <climits>

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

unsigned int min_index(double* tab, int size){
	unsigned int i = 0;
	double tmp = UINT_MAX;
	for (int j = 0; j < size; j++)
	{
		if(tab[j] < tmp){
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
	//Seed that works : 1487181683, 1487182707
	// srand(time(NULL));
	srand(time(NULL));
	printf("seed = %ld\n", time(NULL));

	load_tsv();
    std::string time = CurrentDate();

	std::ofstream best_outfile;
	std::ofstream avg_outfile;
	std::ofstream worst_outfile;
  	best_outfile.open ("./results/"+time+"_best_results.tsv");
  	avg_outfile.open ("./results/"+time+"_avg_results.tsv");
  	worst_outfile.open ("./results/"+time+"_worst_results.tsv");
  	std::string entete = "";
  	entete += "rho_c\ti\tphi_1\tn0\tp\ta\tr1\tteta\tv";
  	best_outfile << entete << "\n";
  	avg_outfile << entete << "\n";
  	worst_outfile << entete << "\n";

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
		unsigned int 		i_worst;
		for (unsigned int fi = 0; fi < pop->size(); fi++)
		{
			fitness[fi] = pop->at(fi)->v() * 1000;
			sum += fitness[fi];
		}

		//Get the worst individual
		i_worst = min_index(fitness, POP_SIZE);
		if(gen%(NB_GEN/10) == 0){
			std::cout << "Worst : " << pop->at(i_worst)->to_tsv_line() <<std::endl;
		}
		worst_outfile << pop->at(i_worst)->to_tsv_line() << "\n";

		//Get the best individual
		i_best = max_index(fitness, POP_SIZE);
		if(gen%(NB_GEN/10) == 0){
			std::cout << "Best  : " << pop->at(i_best)->to_tsv_line() <<std::endl;
		}
		best_outfile << pop->at(i_best)->to_tsv_line() << "\n";

		//Compute the averages and save them
		float roh_c_avg = 0.;
		float i_avg = 0.;
		float phi_1_avg = 0.;
		float n0_avg = 0.;
		float p_avg = 0.;
		float a_avg = 0.;
		float r1_avg = 0.;
		float teta_avg = 0.;
		float v_avg = 0.;
		int total = 0;
		for (unsigned int it = 0; it < pop->size(); it++){
			total++;
			roh_c_avg += pop->at(it)->rho_c->getValue();
			i_avg += pop->at(it)->i->getValue();
			phi_1_avg += pop->at(it)->phi_1->getValue();
			n0_avg += pop->at(it)->n0->getValue();

			p_avg += pop->at(it)->p();
			a_avg += pop->at(it)->a();
			r1_avg += pop->at(it)->r1();
			teta_avg += pop->at(it)->teta();

			v_avg += pop->at(it)->v();
		}
		roh_c_avg /= total;
		i_avg /= total;
		phi_1_avg /= total;
		n0_avg /= total;
		p_avg /= total;
		a_avg /= total;
		r1_avg /= total;
		teta_avg /= total;
		v_avg /= total;

		std::string to_print = "";
		to_print += std::to_string(roh_c_avg);
		to_print += "\t";
		to_print += std::to_string(i_avg);
		to_print += "\t";
		to_print += std::to_string(phi_1_avg);
		to_print += "\t";
		to_print += std::to_string(n0_avg);
		to_print += "\t";
		to_print += std::to_string(p_avg);
		to_print += "\t";
		to_print += std::to_string(a_avg);
		to_print += "\t";
		to_print += std::to_string(r1_avg);
		to_print += "\t";
		to_print += std::to_string(teta_avg);
		to_print += "\t";
		to_print += std::to_string(v_avg);

		avg_outfile << to_print << "\n";


		//Compute the weighted probability
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
	best_outfile.close();
	avg_outfile.close();
	worst_outfile.close();

	delete pop;
	return 0;
}	