#include "../include/Structure.hpp"
#include "../include/Enumeration.hpp"
#include "../include/Descente.hpp"
#include "../include/Recuit.hpp"
#include "../include/Tabou.hpp"

#include <time.h>
#include <stdio.h>

using namespace std;

int main() {
	string nom;
	graphe G;
	int nbSommets, nbAretes, dmin, dmax;

	vector<vector<int>> adj;
	vector<int> degre;

	cout << "Entrez le nom du fichier : " << endl;
	cin >> nom;

	nom = "Graphes/" + nom + "Sommets.txt";

	ifstream fichier(nom);

	//fichier en lecture
	if (fichier) { //si fichier existe
		string mot;
		string ligne;
		while (getline(fichier, ligne)) {
			if (ligne == "# nbSommets nbAretes") {
				fichier >> mot;
				nbSommets = atoi(mot.c_str());
				degre.resize(nbSommets, 0);
				//cout << nbSommets << endl;
				G.nbSommets = nbSommets;
				fichier >> mot;
				nbAretes = atoi(mot.c_str());
				G.nbAretes = nbAretes;
			}
			if (ligne == "# dmin dmax") {
				fichier >> mot;
				dmin = atoi(mot.c_str());
				//cout << dmin << endl;
				fichier >> mot;
				dmax = atoi(mot.c_str());
				//cout << dmax << endl;
			}
			if (ligne == "# source but val") {
				int src, dest, val;
				arc tmp;
				for (int i = 0; i < nbAretes; i++) {
					fichier >> mot;
					src = atoi(mot.c_str());
					fichier >> mot;
					dest = atoi(mot.c_str());
					fichier >> mot;
					val = atoi(mot.c_str());
					tmp.source = src;
					tmp.dest = dest;
					tmp.val = val;
					G.vectorArc.push_back(tmp);
				}
			}
			if (ligne == "# sommet degre") {
				for (int i = 0; i < nbSommets; i++) {
					fichier >> mot >> mot;
					degre[i] = atoi(mot.c_str());
				}
				//AfficheVector(degre);
			}
		}

		adj = MatriceAdj(G);
		Verif(adj, degre, dmin, dmax);
		fichier.close();

		//Affiche(adj);

		int somme = 0;
		vector<int> best_part(nbSommets, 0);

		clock_t t;

		t = clock();
		somme = Fopt(adj, nbSommets, best_part, 3);
		cout << "Enumeration : " << endl;
		Affiche(best_part);
		cout << "Optimum : " << somme << endl;
		t = clock() - t;
		printf("time Enumeration : %f seconds", ((float)t)/CLOCKS_PER_SEC);
		cout << endl;

		t = clock();
		cout << "Descente Gradient : " << endl;
		Gradient(adj, nbSommets, 3);
		t = clock() - t;
		printf("time Descente Gradient : %f seconds",
				((float)t)/CLOCKS_PER_SEC);
		cout << endl;

		t = clock();
		somme = Recuit(adj, nbSommets, 3, best_part);
		cout << "Recuit Simulé : " << endl;
		Affiche(best_part);
		cout << "Optimum : " << somme << endl;
		t = clock() - t;
		printf("time Recuit Simulé : %f seconds", ((float)t)/CLOCKS_PER_SEC);
		cout << endl;

		t = clock();
		somme = Tabou(adj, nbSommets, 3, best_part);
		cout << "Tabou : " << endl;
		Affiche(best_part);
		cout << "Optimum : " << somme << endl;
		t = clock() - t;
		printf("time Tabou : %f seconds", ((float)t)/CLOCKS_PER_SEC);
		cout << endl;

	} else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
	return 0;
}
