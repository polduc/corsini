#ifndef INCLUDE_RECUIT_HPP_
#define INCLUDE_RECUIT_HPP_
#include <vector>
#include "Structure.hpp"
#include <math.h>
#include <string>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;

int Recuit(const vector<vector<int>>&mat,int nbSommets,int k, vector<int>& best_part);
vector<int> rand_voisinage(int nbSommets, vector<int>& part, int k);


#endif /* INCLUDE_RECUIT_HPP_ */
