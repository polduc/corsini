#ifndef INCLUDE_STRUCTURE_HPP_
#define INCLUDE_STRUCTURE_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <list>

using namespace std;
struct arc {
	int source;
	int dest;
	int val;
};
struct graphe {
	int nbSommets;
	int nbAretes;
	vector<arc> vectorArc;
};

vector<vector<int>> MatriceAdj(graphe g);
void Affiche(vector<vector<int>> vec);
void Affiche(vector<int> vec);
void Affiche(list<int> vec);
void Verif(vector<vector<int>> graphe, vector<int> degre, int dmin, int dmax);

int Foptim(const vector<vector<int>>& mat, const vector<int>& partition);

bool Realisable(const vector<int>& classe, int k, int bas, int haut);

#endif /* INCLUDE_STRUCTURE_HPP_ */
