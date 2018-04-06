#ifndef INCLUDE_TABOU_HPP_
#define INCLUDE_TABOU_HPP_
#include <vector>
#include "Structure.hpp"
#include <math.h>
#include <string>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;

int Tabou(const vector<vector<int>>&mat, int nbSommets, int k,
		vector<int>& best_part);
vector<int> voisinage_opt(const vector<vector<int>>& mat, int nbSommets,
		list<vector<int>>& tabou, const vector<int>& part, int k);

#endif /* INCLUDE_TABOU_HPP_ */
