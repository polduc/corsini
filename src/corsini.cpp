#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void AfficheVector(vector<vector<int>> vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[0].size(); j++) {
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

void AfficheVector(vector<int> vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
}

void Verif(vector<vector<int>> graphe, vector<int> degre, int dmin, int dmax) {
	int nbSommets, dmin_aux, dmax_aux, sum;
	bool verif = true;

	nbSommets = degre.size();
	dmin_aux = 10e9; //infini
	dmax_aux = 0;
	sum = 0;
	for (int i = 0; i < nbSommets; i++) {
		for (int j = 0; j < nbSommets; j++) {
			sum += graphe[i][j];
		}
		if (sum != degre[i]) {
			verif = false;
			break;
		}
		if (dmin_aux > sum) {
			dmin_aux = sum;
		}
		if (dmax_aux < sum) {
			dmax_aux = sum;
		}
		sum = 0;
	}
	if (dmin_aux != dmin || dmax_aux != dmax) {
		verif = false;
	}
	if (verif == false) {
		cout << "Erreur de lecture des données !" << endl;
	} else {
		cout << "Lecture des données réalisée avec succès." << endl;
	}
}

int main() {
	string nom;

	int nbSommets, nbAretes, dmin, dmax;

	vector<vector<int>> graphe;
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
				//cout << nbSommets << endl;
				graphe.resize(nbSommets, vector<int>(nbSommets, 0)); //resize le vecteur remplit de 0, c'est à dire aucune liaison entre les sommets
				degre.resize(nbSommets, 0);
				fichier >> mot;
				nbAretes = atoi(mot.c_str());
				//cout << nbAretes << endl;
			} else {
				if (ligne == "# dmin dmax") {
					fichier >> mot;
					dmin = atoi(mot.c_str());
					//cout << dmin << endl;
					fichier >> mot;
					dmax = atoi(mot.c_str());
					//cout << dmax << endl;
				} else {
					if (ligne == "# source but val") {
						int x, y;
						for (int i = 0; i < nbAretes; i++) {
							fichier >> mot;
							x = atoi(mot.c_str());
							fichier >> mot;
							y = atoi(mot.c_str());
							graphe[x - 1][y - 1] = 1;
							graphe[y - 1][x - 1] = 1;
							fichier >> mot;
						}
						//AfficheVector(graphe);
					} else {
						if (ligne == "# sommet degre") {
							for (int i = 0; i < nbSommets; i++) {
								fichier >> mot >> mot;
								degre[i] = atoi(mot.c_str());
							}
							//AfficheVector(degre);
						}
					}
				}
			}
		}
		Verif(graphe, degre, dmin, dmax);
		AfficheVector(graphe);
		fichier.close();
	} else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
		main();
	}
	return 0;
}
