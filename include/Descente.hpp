#ifndef INCLUDE_DESCENTE_HPP_
#define INCLUDE_DESCENTE_HPP_
#include "Structure.hpp"
#include <math.h>
#include <string>
#include <algorithm>
#include <set>
#include <time.h>

int Descente(const vector<vector<int>>& mat, int nbSommets, vector<int> part,
		int k);
void Gradient(const vector<vector<int>>& mat, int nbSommets, int k);

#endif /* INCLUDE_DESCENTE_HPP_ */
