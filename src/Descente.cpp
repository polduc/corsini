#include "../include/Descente.hpp"

int Descente(const vector<vector<int>>& mat, int nbSommets, vector<int> part,
		int k) {
	int Best = 0;
	bool fini = false;
	int place;
	int compteur;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	bool condition;
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
			condition = true;
			for (int j = 0; j < nbSommets; j++) {
				if (bas > voisinage[i][j] || voisinage[i][j] > haut) {
					condition = false;
					break;
				}
			}
			//AfficheVector(voisinage[i]);
			//cout << endl;

			if (condition) {
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
	AfficheVector(part);
	cout << endl;
	return fopt;
}

void Gradient(const vector<vector<int>>& mat, int nbSommets, int k) {
	int fn = 10 * nbSommets;
	int haut = ceil((double) nbSommets / k);
	int bas = nbSommets / k;
	int sum;
	int randNum;
	int j;
	int temp;
	int haut_temp;
	int bas_temp;
	vector<int> config(k);
	vector<int> partition(nbSommets);
	set<int> place;
	for (int n = 0; n < fn; n++) {
		sum = nbSommets;
		j = 0;
		for(int o =0; o< nbSommets; o++){
			place.insert(o);
		}
		haut_temp = haut;
		bas_temp = bas;
		for (int i = k; i > 0; i--) {
			if(bas_temp != haut_temp)
				randNum = rand() % (haut_temp - bas_temp + 1) + bas_temp;
			else
				randNum = bas_temp;
			config[j] = randNum;
			j++;
			sum -= randNum;
			cout<<"sum : "<<sum<<endl;
			cout<<"k : "<<i<<endl;
			haut_temp = ceil((double) sum / i);
			bas_temp = sum / i;
			cout<<"haut : "<<haut_temp<<"bas : "<<bas_temp<<endl;
		}
		//config[j] = sum;

		temp = k;
/*
		for(int l=0;l<k;l++){
			for(int m=config[l];m>0;m--){
				randNum = rand() %k;
				//cout << randNum << endl;
				partition[randNum]=l;
				place.erase(randNum);
				temp--;
			}

		}*/
		AfficheVector(config);
		cout << endl;
		AfficheVector(partition);
		cout << endl;
	}
}

