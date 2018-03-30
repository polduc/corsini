#include "../include/Recuit.hpp"

vector<int> rand_voisinage(int nbSommets, vector<int>& part, int k, int t) {
	vector<vector<int>> voisinage;
	vector<int> temp(nbSommets), classe(k);
	vector<vector<int>>::iterator it;
	//int randNum;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	cout << nbSommets << endl;
	for (int i = 0; i < nbSommets; i++) {
		/*Bug potentiel Ici*/
		for (int j = 0; j < k; j++) {
			if (part[i] != j) {
				temp = part;
				temp[i] = j;
			}
			classe.assign(k, 0);
			for (int j = 0; j < nbSommets; j++) {
				classe[temp[j]] += 1;
			}
			if (Realisable(classe, k, bas, haut)) {
				//cout << "la " << endl;
				voisinage.push_back(temp);
			}
		}
	}
	cout << "voisinage :" << endl;
	for (vector<vector<int>>::iterator it = voisinage.begin();
			it != voisinage.end(); ++it) {
		Affiche(*it);
		cout << endl;
	}
	it = voisinage.begin() + t; //choix X_t dans voisinage de X
	/*randNum = rand() % voisinage.size();
	 advance(it, randNum);
	 cout << "la" << endl;*/
	//Affiche(*it);
	return *it;
}

int Recuit(const vector<vector<int>>& mat, int nbSommets, int k,
		vector<int> best_part) {
	/*initialisation*/

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
	Affiche(best_part);
	cout << endl;
	int fmin = Foptim(mat, partition);
	int T = 1000;
	int cond1 = 0, cond2 = 0;
	int t = 0;
	double p;
	int delta;
	vector<int> voisinage(nbSommets);
	voisinage = rand_voisinage(nbSommets, partition, k, t);
	srand(time(NULL));
	while (cond1 < 100) {
		cout << "cond1" << endl;
		while (cond2 < pow(nbSommets, 2)) {
			cout << "cond2" << endl;
			/*voisinage = rand_voisinage(nbSommets, partition, k, t);
			Affiche(voisinage);*/ // bug dans voisinage
			delta = Foptim(mat, voisinage) - Foptim(mat, partition);
			cout << delta << endl;
			if (delta < 0) {
				partition = voisinage;
				if (Foptim(mat, voisinage) < fmin) {
					best_part = voisinage;
					fmin = Foptim(mat, voisinage);
				}
			} else {
				p = (rand() % 10000 / (double) 10000);
				cout << "p : " << p << endl;
				if (p <= exp(-delta / T)) {
					//partition = rand_voisinage(nbSommets, partition, k, t); bug dans voisinage
					cout << "coucou" << endl;
				}
			}
			t++;
			cond2++;
		}
		cout << "cond2 : " << cond2 << "inf" << pow(nbSommets, 2);
		T *= 0.87;
		cond1++;
		cout << cond1 << endl;
	}
	Affiche(best_part);
	return fmin;
}

