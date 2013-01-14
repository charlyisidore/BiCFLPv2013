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
 * \file Solution.hpp
 * \brief Class of the \c Solution.
 * \author Salim BOUROUGAA & Alban DERRIEN & Axel GRIMAULT & Xavier GANDIBLEUX & Anthony PRZYBYLSKI
 * \date 28 August 2012
 * \version 1.1
 * \copyright 
 *
 * This class represents a solution. In FLP, a solution is representes by two values respectively for the objective 1 and the objective 2.
 *
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include "Data.hpp"
/*! \namespace std
 * 
 * Using the standard namespace std of the IOstream library of C++.
 */
using namespace std;

/*! \class Solution
 * \brief Class to represent a \c Solution.
 *
 *  This class represents a \c Solution with all its two attributes (obj1_ and obj2_).
 */
class Solution
{
public:
  /*!
   *	\brief Default constructor of the class \c Solution.
   */
  Solution();
  /*!
   *	\brief Constructor of the class \c Solution.
   *
   *	\param[in] obj1 : A double which represents the value of the \c Solution w.r.t. objective 1.
   *	\param[in] obj2 : A double which represents the value of the \c Solution w.r.t. objective 2.
   */
  Solution(double obj1, double obj2);
  /*!
   *	\brief Constructor of the class \c Solution.
   *
   *	\param[in] obj1 : A double which represents the value of the \c Solution w.r.t. objective 1.
   *	\param[in] obj2 : A double which represents the value of the \c Solution w.r.t. objective 2.
   *	\param[in] y_j : A string which represents the facilities opened of the \c Solution.
   */
  Solution(double obj1, double obj2, string y_j);

  /*!
   *	\brief Constructor of the class \c Solution.
   *
   *	\param[in] affect : A vector of int. The i-th value of this vector represents the fact that the customer i is served by the facility affect[i].
   *	\param[in] opened_facility : A vector of boolean which represents the facility opened or not.
   *	\param[in] data : The data ofthe instance.
   *	\param[in] rc : The residual capacity of each facility.
   */
  Solution(vector<int> affect, vector<bool> opened_facility, Data & data, vector <double> rc);


  /*!
   *	\brief Destructor of the class \c Solution.
   */
  ~Solution();
    
  /*!
   *	\brief Setter for the value w.r.t objective 1 of this \c Solution.
   *	\param[in] obj : A double which represents the value of the \c Solution w.r.t objective 1.
   */
  void setObj1(double obj);
  /*!
   *	\brief Setter for the value w.r.t objective 2 of this \c Solution.
   *	\param[in] obj : A double which represents the value of the \c Solution w.r.t objective 2.
   */
  void setObj2(double obj);
  /*!
   *	\brief Setter for the value of y_j of this \c Solution.
   *	\param[in] y_j : A String which represents the facilities opened of this \c Solution.
   */
  void setY_j(string y_j);
  /*!
   *	\brief Getter for the value of y_j of this \c Solution.
   *	\return A String which represents the facilities opened of this \c Solution.
   */
  string getY_j() const;
  /*!
   *	\brief Getter for the value w.r.t. objective 1 of this \c Solution.
   *	\return A double as the value w.r.t. objective 1 of this \c Solution.
   */
  double getObj1() const;
  /*!
   *	\brief Getter for the value w.r.t. objective 2 of this \c Solution.
   *	\return A double as the value w.r.t. objective 2 of this \c Solution.
   */
  double getObj2() const;
   
  /*!
   * \brief  Getter for the rank of a \c Solution.
   * \return A unsigned int which represents the rank of this \c Solution.
   */
  unsigned int rank() const;
  /*!
   * \brief  Setter for the rank of a solution.
   * \param[in] rank : A unsigned int which represents the new rank of this \c Solution.
   */
  void setRank(unsigned int rank);
  /*!
   * \brief  Getter that permitts us to know if this \s Solution was ranked or not
   * return A boolean. True if rank = 0, False otherwise
   */
  bool not_yet_ranked();
  /*!
   * \brief  Getter for the crowding value of a \c Solution.
   * \return A double which represents the crowding value of this \c Solution.
   */

  double kappa() const;
  /*!
   * \brief  Setter for the crowding  of a \c Solution.
   * \param[in] kappa : A double which represents the new crowding value of this \c Solution.
   */
  void setKappa(double kappa);
    /*!
   *	\brief Getter for the residual capacity of this \c Solution.
   *	\return A vector of double which represents the redidual capacity of each facility w.r.t. the affectation of this \c Solution.
   */
   
  vector <double> getResidualCapacity() const;
  /*!
   *	\brief Getter for the residual capacity of a facility for this \c Solution.
   *	\param[in] facility : The index of the \c Facility whose we want its residual capacity.
   *	\return A double which represents the residual capacity of facility w.r.t. the affectation of this \c Solution.
   */

  double getResidualCapacity(int facility) const;
  /*!
   *	\brief Setter for the residual capacity of this \c Solution.
   *	\param[in] rc : A vector of double which represents the residual capacity of the \c Solution.
   */
  void setResidualCapacity(vector <double> rc);
  /*!
   *	\brief Getter for the customer affectation of this \c Solution.
   *	\return A vector of int whose the ith value represents the fact that the customer i is affected to the facility value[i].
   */
  vector <int> getAffectation() const;
  /*!
   *	\brief Getter for the index of an \c Facility.
   *	\param[in] customer : The index of the \c Customer whose we want the facility which serves it.
   *	\return An index of a \c Facility.
   */
  int getAffectation(int customer) const;
  

  /*!
   *	\brief Setter for the cusomer affectation of this \c Solution.
   *	\param[in] rc : A vector of int which represents the customer affectation of the \c Solution.
   */
  void setAffectation(vector <int> affectation);

    
private:
  double obj1_;/*!< Double which represents the value w.r.t. objective 1 of this \c Solution */
  double obj2_;/*!< Double which represents the value w.r.t. objective 2 of this \c Solution */
  string y_j_; /*!< String which represents the facility opened of this \c Solution */    
  vector <double> residual_capacity_; /*!< The capacity of each facility w.r.t. the affectation of this \c Solution */    
  vector <int> affectation_; /*!< customer i is affected to a facility affectation_[i]. This slot is used only with cflp */
  unsigned int _rank;   /*!< the rank of the solution. At init, the value is 0, if the solution is efficient, the rank value is 1. ... */
  double _kappa;   /* this value corresponds to the crowding value of this solution. If it is lexicographically efficient in the current population then kappa is +inf (|z|+1); otherwise ... */

};

/*!
 *	\relates Solution
 *	\brief Operator overloading.
 *
 *	Overloading of the comparison operator \c < in order to compare two solutions.
 *	\param[in] s1 : The first \c Solution to compare.
 *	\param[in] s2 : The second \c Solution to compare.
 *	\return A boolean which gets \c TRUE if the value w.r.t. objective 1 of the \c Solution s1 is stricty lower to the value w.r.t. objective 1 of the \c Solution s2, FALSE otherwise.
 */
bool operator< (Solution s1, Solution s2);
/*!
 *	\relates Solution
 *	\brief Operator overloading.
 *
 *	Overloading of the comparison operator \c < in order to compare two solutions.
 *	\param[in] s1 : The first \c Solution to compare.
 *	\param[in] s2 : The second \c Solution to compare.
 *	\return A boolean which gets \c TRUE if the value w.r.t. objective 1 of the \c Solution s1 is stricty lower to the value w.r.t. objective 1 of the \c Solution s2, FALSE otherwise.
 */

bool operator<=(Solution const &s1 ,Solution const & s2);

bool operator==(Solution const &s1 ,Solution const & s2);


/*!
 *	\relates Solution
 *	\brief Operator overloading.
 *
 *	Overloading of the standard output stream in order to print a \c Customer.
 *	\param[out] out : The standard output stream.
 *	\param[in] sol : A \c Solution to print in the standard output stream.
 */
ostream& operator<<(ostream &out, const Solution *sol);

#endif

