#include "../include/Enumeration.hpp"

int Fopt(const vector<vector<int>>& mat, int nbSommets, vector<int>& best_part,
		int k) {
	int Best = -1;
	int fopt = 1e9;
	int foptim;
	int nb, modulo, quotient, f, code;
	vector<int> p(nbSommets);
	if (k == 2) {
		for (int i = 0; i < pow(2, nbSommets - 1); i++) {
			nb = i;
			for (int j = nbSommets - 1; j > 0; j--) {
				quotient = nb / 2;
				modulo = nb % 2;
				nb = quotient;
				p[j] = modulo;
			}
			code = 0;
			for (int i = 0; i < nbSommets; i++) {
				f = 2 * p[i] - 1;
				code += f;
			}

			if (code == 0 or code == -1 or code == 1) {
				for (int i = nbSommets - 1; i >= 0; i--) {

				}
				int foptim = Foptim(mat, p);
				if (foptim < fopt) {
					Best = i;
					fopt = foptim;
					best_part = p;
				}
			}
		}
		AfficheVector(best_part);
		cout << endl;
		return fopt;
	} else {
		vector<int> classe(k, 0);
		int haut = ceil((double) nbSommets / k);
		int bas = nbSommets / k;
		bool condition;
		for (int i = 0; i < pow(k, (nbSommets))/2; i++) {
			nb = i;
			condition = true;
			for (int j = nbSommets-1; j >= 0; j--) {
				quotient = nb / k;
				modulo = nb % k;
				nb = quotient;
				p[j] = modulo;
			}
			code = 0;
			for (auto k : p)
				cout << " " << k;
			cout << endl;
			classe.assign(k, 0);
			for (int i = 0; i < nbSommets; i++) {
				classe[p[i]] += 1;
			}
			for (int i = 0; i < k; i++) {
				if (bas > classe[i] || classe[i] > haut) {
					condition = false;
					break;
				}
			}
			if (condition) {
				foptim = Foptim(mat, p);
				if (foptim < fopt) {
					Best = i;
					fopt = foptim;
					best_part = p;
				}
			}
		}
		AfficheVector(best_part);
		cout << endl;
		return fopt;
	}
	return 0;
}

