#include "../include/Structure.hpp"

vector<vector<int>> MatriceAdj(graphe g) {

	vector<vector<int>> mat;
	vector<arc>::iterator It1, It2;

	mat.resize(g.nbSommets);
	for (int i = 0; i < g.nbSommets; i++) {
		mat[i].resize(g.nbSommets);
	}

	for (int i = 0; i < g.nbSommets; i++) {
		for (int j = 0; j < g.nbSommets; j++) {
			mat[i][j] = 0;
		}
	}

	for (It1 = g.vectorArc.begin(); It1 != g.vectorArc.end(); It1++) {
		mat[(*It1).source - 1][(*It1).dest - 1] = (*It1).val;
		mat[(*It1).dest - 1][(*It1).source - 1] = (*It1).val;
	}

	return mat;
}

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

int Foptim(const vector<vector<int>>& mat, const vector<int>& part) {
	int somme = 0;
	for (size_t i = 0; i < part.size() - 1; i++) {
		for (size_t j = i; j < part.size(); j++) {
			if (part[i] != part[j]) {
				somme += mat[i][j];
			}
		}
	}
	return somme;
}


