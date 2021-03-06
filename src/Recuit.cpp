#include "../include/Recuit.hpp"

vector<int> rand_voisinage(int nbSommets, vector<int>& part, int k) {
	vector<vector<int>> voisinage;
	vector<int> temp(nbSommets), classe(k);
	vector<vector<int>>::iterator it;
	int randNum;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	for (int i = 0; i < nbSommets; i++) {
		for (int j = 0; j < k; j++) {
			if (part[i] != j) {
				temp = part;
				temp[i] = j;
				classe.assign(k, 0);
				for (int j = 0; j < nbSommets; j++) {
					classe[temp[j]] += 1;
				}
				if (Realisable(classe, k, bas, haut)) {
					//Affiche(temp);
					voisinage.push_back(temp);
				}
			}
		}
	}

	it = voisinage.begin();
	randNum = rand() % voisinage.size();
	advance(it, randNum);
	return *it;
}

int Recuit(const vector<vector<int>>& mat, int nbSommets, int k,
		vector<int>& best_part) {
	/*choix sol initiale*/
	int haut = ceil((double) nbSommets / k);
	int randNum;
	int temp_s;
	int temp_k;
	int haut_temp;
	srand(time(NULL));
	vector<int> config_ini(k);
	vector<int> partition(nbSommets);
	set<int> place_part;
	set<int> place_config;
	set<int>::iterator it;
	for (int i = 0; i < nbSommets; i++) {
		place_part.insert(i);
	}
	for (int i = 0; i < k; i++) {
		place_config.insert(i);
	}
	haut_temp = haut;
	temp_s = nbSommets;
	temp_k = k;
	config_ini.assign(k, 0);
	for (int i = k - 1; i > 0; i--) {
		randNum = rand() % temp_k;
		it = place_config.begin();
		advance(it, randNum);
		config_ini[*it] = haut_temp;
		place_config.erase(*it);
		temp_k--;
		temp_s -= haut_temp;
		haut_temp = ceil((double) temp_s / i);
	}
	it = place_config.begin();
	config_ini[*it] = temp_s;
	temp_s = nbSommets;
	for (int l = 0; l < k; l++) {
		for (int m = config_ini[l]; m > 0; m--) {
			randNum = rand() % temp_s;
			it = place_part.begin();
			advance(it, randNum);
			partition[*it] = l;
			place_part.erase(*it);
			temp_s--;
		}
	}
	best_part = partition;
	int fmin = Foptim(mat, partition);
	double T = 1000;
	int cond1 = 0, cond2 = 0;
	double p;
	int delta;
	int ftemp;
	vector<int> voisinage(nbSommets);
	voisinage = rand_voisinage(nbSommets, partition, k);
	srand(time(NULL));
	while (cond1<100) {
		cond2 = 0;
		while (cond2 < pow(nbSommets, 2)) {
			voisinage = rand_voisinage(nbSommets, partition, k);
			//Affiche(voisinage);
			delta = Foptim(mat, voisinage) - Foptim(mat, partition);
			if (delta < 0) {
				partition = voisinage;
				ftemp = Foptim(mat, voisinage);
				if (ftemp < fmin) {
					best_part = voisinage;
					fmin = ftemp;

				}
			} else {
				p = (rand() % 10000 / (double) 10000);
				if (T > 1e-6 && p <= (double) exp(-delta / T)) {
					partition = rand_voisinage(nbSommets, partition, k); //bug dans voisinage
				}
			}
			cond2++;
		}
		T *= 0.87;
		cond1++;
	}
	return fmin;
}

