/*
 #License and Copyright
 
 #Version : 1.1
 
 #This file is part of BiUFLv2012.
 
 #BiUFLv2012 is Copyright © 2012, University of Nantes
 
 #BiUFLv2012 is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 
 #This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 
 #You should have received a copy of the GNU General Public License along with this program; if not, you can also find the GPL on the GNU web site.
 
 #In addition, we kindly ask you to acknowledge BiUFLv2012 and its authors in any program or publication in which you use BiUFLv2012. (You are not required to do so; it is up to your common sense to decide whether you want to comply with this request or not.) For general publications, we suggest referencing:  BiUFLv2012, MSc ORO, University of Nantes.
 
 #Non-free versions of BiUFLv2012 are available under terms different from those of the General Public License. (e.g. they do not require you to accompany any object code using BiUFLv2012 with the corresponding source code.) For these alternative terms you must purchase a license from Technology Transfer Office of the University of Nantes. Users interested in such a license should contact us (valorisation@univ-nantes.fr) for more information.
 */

/*!
* \file NSGA2.hpp
* \brief contains the evolutionary genetic algorithm NSGA-II
* \author Mohamed CISSE & Takfarinas SABER & Salim BOUROUGAA & Alban DERRIEN & Axel GRIMAULT & Xavier GANDIBLEUX & Anthony PRZYBYLSKI
* \date 28 August 2012
* \version 1.1
* \copyright GNU General Public License 
*
* This file groups all the functions for NSGA-II algorithm.
*
*/

#ifndef NSGA2_H
#define NSGA2_H

#include "ToFile.hpp"
#include "CflpFunctions.hpp"
#include "Solution.hpp"
#include "Box.hpp"
#include <algorithm>
#define DIMENSION 2
/**
 * these comparaisons are useful for the function sort 
 **/

bool z1_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2);
bool z2_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2);
bool crowding_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2);

Solution * tournament(Solution * father1, Solution * father2);

unsigned int ranking(std::vector<Solution*> &population);
void crowding (std::vector<Solution*> &population);

/**
 * \fn void initialisation (Efficient_sol &population_efficace, std::vector<Solution*> &population, unsigned int numberOfLambda, std::vector<Box*> vectorBoxFinal, Data & data) 
 *
 * \brief get the first population using the reparation of former found solutions
 * \param population_efficace empty vector which will contain efficient solutions
 * \param std::vector<Solution*> &population empty vector which will contain the initial correct population 
 * \param other parameters are those of the function reparation see function "repare" for mor details
 **/

void initialization(EfficientSolution & efficient_population,
		    std::vector<Solution*> &population,  
		    unsigned int numberOfLambda,
		    std::vector<Box*> vectorBoxFinal,
		    Data & data);

void  evolution (EfficientSolution & efficient_population, 
		 std::vector <Solution*> &population, 
		 std::vector <Solution*> &offspring_population, 
		 double P_c, 
		 double P_m,
		 Data & data);

void nsga2(vector<Solution* > &initial_population,
		   EfficientSolution &efficient_population, 
	  unsigned int numberOfLambda,
	  std::vector<Box*> vectorBoxFinal,
	  double P_c,
	  double P_m,
	  unsigned int nGenerations,
	  Data & data);

#endif //NSGA2_H
