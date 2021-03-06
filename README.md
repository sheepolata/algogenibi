#Utilisation
Attention, le programme Python **ne fonctionne pas**.

Pour lancer le programme C++, deux solutions :
* Utiliser le MakeFile (Les règles `Make clean` et `Make run` sont implémentées).
* Utiliser le fichier *command.sh* de la manière suivante : `./ command.sh <nb_run>`. \<nb_run\> représente le nombre de fois que l'algorithme est lancer, et **non** le nombre de génération. Pour changer le nombre de génération, il faut modifier les variables globales dans le fichier *parameters.hpp*.

Les résultats des runs de l'algorithme sont enregistrés dans trois fichiers :

Ces trois fichiers sont présent dans un dossier *results* à la racine du projet C++.

**Attention**, si ce dossier **n'existe pas** lors du lancement du programme, l'enregistrement ne fonctionnera probablement pas. Il faut alors simplement créer un dossier vide nommer *results* à la racine du projet C++.

* timestamp_avg_results.tsv : enregistrement de la moyenne des paramètres et fonction (`rho_c`, `i`, `phi_1`, `n0`, `p()`, `a()`, `r1()`, `teta()` et `v()`) pour chaque génération.
* timestamp_best_results.tsv : enregistrement des paramètres et fonction (`rho_c`, `i`, `phi_1`, `n0`, `p()`, `a()`, `r1()`, `teta()` et `v()`) du **meilleur individu** pour chaque génération.
* timestamp_worst_results.tsv : enregistrement des paramètres et fonction (`rho_c`, `i`, `phi_1`, `n0`, `p()`, `a()`, `r1()`, `teta()` et `v()`) du **pire individu** pour chaque génération.
