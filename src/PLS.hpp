#ifndef PLS_H
#define PLS_H
#include <algorithm>
#include <vector>
#include <stdio.h>
#include "Solution.hpp"
#include "EfficientSolution.hpp"
#include "Data.hpp"
#include "NSGA2.hpp"
#include "Argument.hpp"

extern bool gnuplotPLS;
using namespace std;



bool localSearch1opt(EfficientSolution & efficient_sol, Solution* s, Data & data);
bool localSearchSwap(EfficientSolution & efficient_sol, Solution* s, Data & data);
bool localSearch2opt(EfficientSolution & efficient_sol, Solution* s, Data & data);
void paretoLocalSearch(EfficientSolution & efficient_sol, unsigned int nbBoxes, int nbIteration, Data & data);


#endif
