#include "../include/Descente.hpp"

int Descente(const vector<vector<int>>& mat, int nbSommets, vector<int>& part,
		int k) {
	int Best = 0;
	bool fini = false;
	int place;
	int compteur;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	int fopt = Foptim(mat, part);
	vector<int> classe(k);
	int foptim;
	vector<vector<int>> voisinage((k - 1) * nbSommets, vector<int>(nbSommets));
	while (fini == false) {
		fini = true;
		place = 0; //permet de placer la partition a la bonne place dans le voisinage
		for (int i = 0; i < nbSommets; i++) {
			compteur = 0;
			for (int j = 0; j < k; j++) {
				if (part[i] != j) {
					voisinage[place + compteur] = part;
					voisinage[place + compteur][i] = j;
					compteur++;
				}
			}
			place += (k - 1);
		}
		for (int i = 0; i < (k - 1) * nbSommets; i++) {
			classe.assign(k, 0);
			for (int j = 0; j < nbSommets; j++) {
				classe[voisinage[i][j]] += 1;
			}

			if (Realisable(classe, k, bas, haut)) {
				foptim = Foptim(mat, voisinage[i]);
				if (foptim < fopt) {
					Best++;
					fopt = foptim;
					part = voisinage[i];
					fini = false;
				}
			}
		}
	}
	return fopt;
}

void Gradient(const vector<vector<int>>& mat, int nbSommets, int k) {
	int fn = 10 * nbSommets;
	int haut = ceil((double) nbSommets / k);
	int randNum;
	int temp_s;
	int temp_k;
	int haut_temp;
	int tmp = 0;
	int min = 1e9;
	int max = 0;
	double mean;
	int sum = 0;
	srand(time(NULL));
	vector<int> config(k);
	vector<int> best_part(nbSommets);
	vector<int> partition(nbSommets);
	set<int> place_part;
	set<int> place_config;
	set<int>::iterator it;
	for (int n = 0; n < fn; n++) {
		for (int i = 0; i < nbSommets; i++) {
			place_part.insert(i);
		}
		for (int i = 0; i < k; i++) {
			place_config.insert(i);
		}
		haut_temp = haut;
		temp_s = nbSommets;
		temp_k = k;
		config.assign(k, 0);
		for (int i = k - 1; i > 0; i--) {
			randNum = rand() % temp_k;
			it = place_config.begin();
			advance(it, randNum);
			config[*it] = haut_temp;
			place_config.erase(*it);
			temp_k--;
			temp_s -= haut_temp;
			haut_temp = ceil((double) temp_s / i);
		}
		it = place_config.begin();
		config[*it] = temp_s;
		temp_s = nbSommets;
		for (int l = 0; l < k; l++) {
			for (int m = config[l]; m > 0; m--) {
				randNum = rand() % temp_s;
				it = place_part.begin();
				advance(it, randNum);
				partition[*it] = l;
				place_part.erase(*it);
				temp_s--;
			}
		}
		tmp = Descente(mat, nbSommets, partition, k);

		if (tmp > max)
			max = tmp;
		if (tmp < min){
			min = tmp;
			best_part = partition;
		}
		sum += tmp;
	}
	Affiche(best_part);
	mean = (double) (sum / fn);
	cout << "min : " << min << endl;
	cout << "max : " << max << endl;
	cout << "mean : " << mean << endl;
}

