#include "../include/Structure.hpp"
#include "../include/Enumeration.hpp"
#include "../include/Descente.hpp"
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
		//AfficheVector(adj);
		fichier.close();

		vector<vector<int>> G1(4, vector<int>(4, 0));
		vector<vector<int>> G2(3, vector<int>(3, 0));

		G1[0][1] = 1;
		G1[0][2] = 1;
		G1[1][2] = 1;
		G1[2][3] = 1;
		G1[3][3] = 1;
		//AfficheVector(G1);

		G2[0][1] = 1;
		G2[0][2] = 1;
		G2[1][2] = 1;
		//AfficheVector(G2);

		/*
		 vector<int> part(3);
		 part[0] = 0;
		 part[1] = 0;
		 part[2] = 1;
		 //AfficheVector(part);
		 cout << endl;
		 */

		vector<vector<int>> G3(6, vector<int>(6, 0));
		vector<vector<int>> G4(10, vector<int>(10, 0));

		G3[1 - 1][2 - 1] = 1;
		G3[1 - 1][3 - 1] = 1;
		G3[1 - 1][5 - 1] = 1;
		G3[1 - 1][6 - 1] = 1;
		G3[2 - 1][3 - 1] = 1;
		G3[3 - 1][4 - 1] = 1;
		G3[4 - 1][4 - 1] = 1;
		G3[4 - 1][5 - 1] = 1;
		G3[5 - 1][6 - 1] = 1;
		//AfficheVector(G3);

		for (int i = 1; i <= 10; i++) {
			if (2 * i <= 10) {
				G4[i - 1][2 * i - 1] = 1;
			}
			if (3 * i <= 10) {
				G4[i - 1][3 * i - 1] = 1;
			}
			if (5 * i <= 10) {
				G4[i - 1][5 * i - 1] = 1;
			}
		}
		//AfficheVector(G4);
		Affiche(adj);
		int somme;
		vector<int> best_part;
		/*somme = Fopt(adj, nbSommets, best_part, 3);
		cout << somme << endl;
		cout << endl;
		somme = Descente(adj, nbSommets, best_part, 3);
		cout << somme << endl;*/

		Gradient(G1, 4, 3);

	} else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
	return 0;
}
