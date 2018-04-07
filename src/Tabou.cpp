#include "../include/Tabou.hpp"

vector<int> voisinage_opt(const vector<vector<int>>& mat, int nbSommets,
		list<vector<int>>& tabou, const vector<int>& part, int k) {
	vector<int> best_part;
	vector<int> temp(nbSommets), classe(k);
	vector<vector<int>>::iterator it;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	int foptim = 1e9;
	int ftemp;
	bool is_tabou;
	int temp_i = -1;
	int temp_j = -1;
	for (int i = 0; i < nbSommets; i++) {
		for (int j = 0; j < k; j++) {
			is_tabou = false;
			for (auto l : tabou) {
				if (l[0] == i && l[1] == j) {
 					is_tabou = true;
				}
			}
			if (part[i] != j && is_tabou == false) {
				temp = part;
				temp[i] = j;
				classe.assign(k, 0);
				for (int j = 0; j < nbSommets; j++) {
					classe[temp[j]] += 1;
				}
				if (Realisable(classe, k, bas, haut)) {
					ftemp = Foptim(mat, temp);
					if (ftemp < foptim) {
						best_part = temp;
						temp_i = i;
						temp_j = j;
						foptim = ftemp;
					}
				}
			}

		}
	}
	tabou.pop_front(); //mise a jour tabou
	tabou.push_back({temp_i, temp_j});

	return best_part;
}

int Tabou(const vector<vector<int>>&mat, int nbSommets, int k,
		vector<int>& best_part) {
	/*choix sol initiale*/
	int haut = ceil((double) nbSommets / k);
	int randNum;
	int temp_s;
	int temp_k;
	int haut_temp;
	srand(time(NULL));
	vector<int> config_ini(k);
	vector<int> partition_X(nbSommets);
	vector<int> partition_Y(nbSommets);
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
			partition_X[*it] = l;
			place_part.erase(*it);
			temp_s--;
		}
	}
	best_part = partition_X;

	int fmin = Foptim(mat, partition_X);
	int ftemp;
	int IterMax = 500;
	list<vector<int>> tabou;
	vector<int> temp(2, -1);
	int val;
	if(nbSommets <= 5)
		val = 3;
	else
		val = 7;
	for (int t = 0; t < val; t++) {
		tabou.push_back(temp);
	}
	int iter = 0;
	while (iter < IterMax) {
		iter++;
		partition_Y = voisinage_opt(mat, nbSommets, tabou, partition_X, k);
		ftemp = Foptim(mat, partition_Y);
		if(ftemp < fmin){
			best_part = partition_Y;
			fmin = ftemp;
		}
		//tabou mis a jour dans voisinage_opt
		partition_X = partition_Y;
	}

	return fmin;
}
