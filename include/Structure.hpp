#ifndef INCLUDE_STRUCTURE_HPP_
#define INCLUDE_STRUCTURE_HPP_

#include <iostream>
#include <fstream>
#include <vector>

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
void AfficheVector(vector<vector<int>> vec);
void AfficheVector(vector<int> vec);
void Verif(vector<vector<int>> graphe, vector<int> degre, int dmin, int dmax);

int Foptim(const vector<vector<int>>& mat, const vector<int>& partition);

#endif /* INCLUDE_STRUCTURE_HPP_ */
