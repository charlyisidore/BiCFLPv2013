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

#include "Solution.hpp"

Solution::Solution()
{
}

Solution::Solution(double obj1, double obj2)
{
  obj1_ = obj1;
  obj2_ = obj2;
}


Solution::Solution(double obj1, double obj2, string y_j)
{
  obj1_ = obj1;
  obj2_ = obj2;
  y_j_  = y_j;
}

Solution::Solution(vector<int> affect, vector <bool> opened_facility, Data & data, vector <double> rc)
{
  obj1_ = 0.;
  obj2_ = 0.;
  
  unsigned int numberOfFacility = data.getnbFacility();
  //unsigned int numberOfCustomers = data.getnbCustomer();
  
  vector<bool> added_cost_of_facility = vector<bool>();
  for(unsigned int i=0; i<numberOfFacility;i++){
	  added_cost_of_facility.push_back(false);
  }
  

    
  for (unsigned int i=0; i<affect.size(); ++i)
    {
      affectation_.push_back(affect[i]);
      obj1_ += data.getAllocationObj1Cost(i,affect[i]);
      obj2_ += data.getAllocationObj2Cost(i,affect[i]);
      if(!added_cost_of_facility[affect[i]]){
			obj1_ += data.getFacility(affect[i]).getLocationObj1Cost();
			obj2_ += data.getFacility(affect[i]).getLocationObj2Cost();
			added_cost_of_facility[affect[i]]=true;
	  }
    }
  for (unsigned int i=0; i < rc.size(); ++i)
    {
      residual_capacity_.push_back(rc[i]);
    }
    
    

	   for(unsigned int i=0; i< opened_facility.size(); i++)
    {
      if (added_cost_of_facility[i]){
	y_j_ += "1";
      }
      else{
	y_j_ += "0";
      }
    }
   
}



Solution::~Solution()
{
}

void Solution::setObj1(double obj)
{
  obj1_ = obj;
}

void Solution::setObj2(double obj)
{
  obj2_ = obj;
}

void Solution::setY_j(string y_j)
{
  y_j_ = y_j;
}

string Solution::getY_j() const
{
  return y_j_;
}

double Solution::getObj1() const
{
  return obj1_;
}

double Solution::getObj2() const
{
  return obj2_;
}

unsigned int Solution::rank() const{
  return _rank;
}

void Solution::setRank(unsigned int rank){
  _rank = rank;
}

bool Solution::not_yet_ranked(){
  return _rank == 0;
}


double Solution::kappa() const {
  return _kappa;
}

void Solution::setKappa(double kappa){
  _kappa = kappa;
}



bool operator< (Solution s1, Solution s2)
{
  return s1.getObj1() < s2.getObj1();
}

bool operator<=(Solution const &  s1 ,Solution const & s2)
{
  return ( ( (s1.getObj1()) <= (s2.getObj1())  &&  (s1.getObj2()) < (s2.getObj2()))  || 
	   ( (s1.getObj1()) < (s2.getObj1())  &&  (s1.getObj2()) <= (s2.getObj2())));
}
bool operator==(Solution const &  s1 ,Solution const & s2)
{
  if (s1.getObj1() != s2.getObj1())
    return false;
  if (s1.getObj2() != s2.getObj2())
    return false;

  for(unsigned int i=0; i<s1.getAffectation().size();i++){
    if (s1.getAffectation(i) != s2.getAffectation(i))
      return false;
  }
  return true;
}


vector <double> Solution::getResidualCapacity() const
{
  return residual_capacity_;
}

double Solution::getResidualCapacity(int facility) const
{
  return residual_capacity_[facility];
}


void Solution::setResidualCapacity(vector <double> rc)
{

  for (unsigned int i=0; i < rc.size(); ++i)
    {
      residual_capacity_[i] = rc[i];
    }
}

vector <int> Solution::getAffectation() const
{
  return affectation_;
}

int Solution::getAffectation(int customer) const
{
  return affectation_[customer];
}


void Solution::setAffectation(vector <int> affectation)
{
  for (unsigned int i=0; i<affectation.size(); ++i)
    {
      affectation_[i] = affectation[i];
    }
}

ostream &operator<<(ostream &out, const Solution *sol)
{
  out << sol->getObj1() << "\t" << sol->getObj2() ;//<< "\t"<< sol->getY_j()<<"\t";
  /* // if needs for debug
  for(unsigned int i=0;i<sol->getAffectation().size();i++){
	 out << sol->getAffectation(i)<<" ";
  }	
  */
  return out;
}

