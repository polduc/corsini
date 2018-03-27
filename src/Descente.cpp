#include "../include/Descente.hpp"

int Descente(const vector<vector<int>>& mat, int nbSommets, vector<int> part,
		int k) {
	int Best = 0;
	bool fini = false;
	int place;
	int compteur;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	int fopt = Foptim(mat, part);
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
			Affiche(voisinage[i]);
			cout << endl;
			if (Realisable(voisinage[i], k, bas, haut)) {
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
	cout << endl;
	Affiche(part);
	cout << endl;
	return fopt;
}

void Gradient(const vector<vector<int>>& mat, int nbSommets, int k) {
	int fn = 10 * nbSommets;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	int randNum;
	int temp_s;
	int temp_k;
	int haut_temp;
	int bas_temp;
	srand (time(NULL));
	vector<int> config(k);
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
		bas_temp = bas;
		temp_s = nbSommets;
		temp_k = k;
		config.assign(k, 0);
		for (int i = k - 1; i > 0; i--) {
			randNum = rand() % temp_k;
			it = place_config.begin();
			advance(it, randNum);
			randNum = rand() % (haut_temp - bas_temp + 1) + bas_temp;
			config[*it] = randNum;
			place_config.erase(*it);
			temp_k--;
			temp_s -= randNum;
			haut_temp = ceil((double) temp_s / i);
			bas_temp = temp_s / i;
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
		Affiche(config);
		cout << endl;
		Affiche(partition);
		cout << endl;
	}
}

