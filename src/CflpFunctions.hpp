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
* \file CflpFunctions.hpp
* \brief A set of functions useful for capacitated facility location problem.
* \author Mohamed CISSE & Takfarinas SABER & Salim BOUROUGAA & Alban DERRIEN & Axel GRIMAULT & Xavier GANDIBLEUX & Anthony PRZYBYLSKI
* \date 28 August 2012
* \version 1.1
* \copyright GNU General Public License 
*
* This file groups all the functions for solving CFLP problem which are not methods of Class.
*
*/


#ifndef CFLP_FUNCTIONS_H
#define CFLP_FUNCTIONS_H

#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "Data.hpp"
#include "Solution.hpp"
#include "EfficientSolution.hpp"


/*!
*	\defgroup random Random Methods
*/


/**
 * \fn double randomGeneration(double XMIN , double XMAX)
 * \brief returns a value in the interval [X_MIN, X_MAX]
 *
 * \param[in] XMIN The minimum value of x. (XMIN included)
 * \param[in] XMAX The maximum value of x. (XMAX included)
 * \return A value in the interval [XMIN, XMAX]
 */
double randomGeneration(double XMIN , double XMAX);

/**
 * \fn double frandAB(double a, double b)
 * \brief returns a value in the interval [a, b[
 *
 * \param[in] a The minimum value of x. (a included)
 * \param[in] b The maximum value of x. (b excluded)
 * \return A value in the interval [a, b]
 */
double frandAB(double a, double b);

/**
 * \fn randAB(int a, int b)
 * \brief returns an interger number between a and b included
 * \param[in] a The minimum value of x. (a included)
 * \param[in] b The maximum value of x. (b excluded)
 * \return A value in the interval [a, b]
*/
int randAB(int a, int b);


/*!
* \defgroup CFLP CFLP Methods
*/


/*!
* \fn repare(Data &data, vector<bool> & opened_facility, double numberOfLambda)
* \ingroup others
* \brief This method creates  set of solution w.r.t. capacity constraint which has been relaxed during previous phase.
* \param[in] data : A \c Data object which contains all the values of the instance.
* \param[in] opened_facility : A vector of bool which represents the opened facilities
* \param[in] numberOfLambda : The number of times we are going to generate lambda (between 0 and 1)
* \param[in] X_e : pareto frontier
* \return A vector of pointer of \c Solution respecting the capacity constraint.
*/
vector <Solution *> repare(Data &data,
			   vector<bool> & opened_facility, 
			   double numberOfLambda,
			   EfficientSolution & X_e);

/**
 * \fn std::vector< Solution* > path_relinking(Data &data, Solution* s1, Solution* s2, Efficient_sol & X_e)
 * \brief designs a path relinking two solutions given as parameters
 * \param[in] s1 a pointer to a \c Solution to link to an other
 * \param[in] s2 a pointer to a \c Solution to link to s1
 * \param[in] X_e : pareto frontier
 * \return the visited solutions through the path
 */

vector< Solution* > path_relinking( Data &data,
				    Solution* s1, 
				    Solution* s2, 
				    EfficientSolution & X_e);
#endif // CFLP_FUNCTIONS_H

