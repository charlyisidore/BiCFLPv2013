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


#ifndef EFFICIENT_SOL_H
#define EFFICIENT_SOL_H

/*!
 * \file Customer.hpp
 * \brief Class of the \c EfficientSolution
 * \author CISSE & SABER
 * \date 28 August 2012
 * \version 1.1
 * \copyright 
 *
 * This class manage a set of non dominated solutions a maintains it during the execution
 *
 */

#include <vector>
#include "Solution.hpp"

/*! \class EfficientSolution
 * \brief Class to represent a \c EfficientSolution
 *
 *  For each \c Solution in an instance of this class, we didn't find "until now", any \c Solution which dominates it
 */



/*! \class EfficientSolution
 * \brief contains the whole solutions such that: 
 * for each one of them, we didn't find "until now", any solution which dominates it
 */
class EfficientSolution
{

public:
  /*!
   * \brief default constructor
   * 
   */
  EfficientSolution();

  /*!
   * \brief Getter of the set of non dominated solutions (until now)
   * 
   */
  std::vector<Solution*> X_e() const;


  Solution * operator[](unsigned int index);


  /*!
   * \brief returns the number of efficient solutions
   * 
   */
  
  unsigned int size() const;

  /*!
   * \brief Add a \c Solution s to the non dominated-set if it's (s) non dominated and delete the dominated element from it  
   * \param[in] s : A pointer to the solution to add
   */
  bool addSolution(Solution* s);
		

  /*!
   * \brief the deleter
   * 
   */
  ~EfficientSolution();
		
private:
  std::vector<Solution*> _X_e; /*!< the Set of non domated points until the curent time*/

};



#endif // EFFICIENT_SOL_H
