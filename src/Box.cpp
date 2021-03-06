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
 
#include "Box.hpp"

Box::Box(Data &data):
  data_(data)
{
  //Set opening of depots to FALSE
  facility_ = new bool[data_.getnbFacility()];
  for(unsigned int i = 0; i < data_.getnbFacility(); ++i)
    {
      facility_[i] = false;
    }
	
  //Set allocation of customer to FALSE
  isAssigned_ = new bool[data_.getnbCustomer()];
  for(unsigned int i = 0; i < data_.getnbCustomer(); ++i)
    {
      isAssigned_[i] = false;
    }
    
  //All cost are 0 (nothing is allocated)
  nbCustomerNotAffected_ = data_.getnbCustomer();
  minZ1_ = 0;
  minZ2_ = 0;
  maxZ1_ = 0;
  maxZ2_ = 0;
  originZ1_ = 0;
  originZ2_ = 0;
  id_ = "";
}

Box::Box(Box* copy):
  data_(copy->data_)
{
    
  //Set Facilities
  facility_ = new bool[data_.getnbFacility()];
  for(unsigned int i = 0; i < data_.getnbFacility(); ++i)
    {
      facility_[i] = copy->facility_[i];
    }
	
  //Set Customers
  isAssigned_ = new bool[data_.getnbCustomer()];
  for(unsigned int i = 0; i < data_.getnbCustomer(); ++i)
    {
      isAssigned_[i] = copy->isAssigned_[i];
    }
	
  nbCustomerNotAffected_ = copy->nbCustomerNotAffected_;
  minZ1_ = copy->minZ1_;
  minZ2_ = copy->minZ2_;
  maxZ1_ = copy->maxZ1_;
  maxZ2_ = copy->maxZ2_;
  originZ1_ = copy->originZ1_ ;
  originZ2_ = copy->originZ2_;
  id_ = copy->id_;
  hasMoreStepWS_ = copy->hasMoreStepWS_;
  hasNeighbor_ = copy->hasNeighbor_;
}

Box::Box(Data& data, bool *toOpen):
  data_(data)
{
  nbCustomerNotAffected_ = data_.getnbCustomer();
  minZ1_ = 0;
  minZ2_ = 0;
  maxZ1_ = 0;
  maxZ2_ = 0;
  originZ1_ = 0;
  originZ2_ = 0;
  id_ = "";
  hasMoreStepWS_ = true; // A priori, some supported points exist
  hasNeighbor_ = false;
	
  //Set opening of depots to FALSE
  facility_ = new bool[data_.getnbFacility()];
  for(unsigned int i = 0; i < data_.getnbFacility(); ++i)
    {
      facility_[i] = false;
      if (toOpen[i])
	{
	  openFacility(i);
	  id_ += "1";
	}
      else
	{
	  id_ += "0";
	}
    }
  //Set allocation of customer to FALSE
  isAssigned_ = new bool[data_.getnbCustomer()];
  for(unsigned int i = 0; i < data_.getnbCustomer(); ++i)
    {
      isAssigned_[i] = false;
    }	
}

Box::~Box()
{
  delete[] facility_;
  delete[] isAssigned_;
}

double Box::getMinZ1() const
{
  return minZ1_;
}

double Box::getMinZ2() const
{
  return minZ2_;
}

double Box::getMaxZ1() const
{
  return maxZ1_;
}

double Box::getMaxZ2() const
{
  return maxZ2_;
}

double Box::getOriginZ1() const
{
  return originZ1_;
}

double Box::getOriginZ2() const
{
  return originZ2_;
}

string Box::getId() const
{
  return id_;
}

bool Box::isAssigned(int cust) const
{
  return isAssigned_[cust];
}

bool Box::isOpened(int fac) const
{
  return facility_[fac];
}

bool* Box::y_j() const
{
  return facility_;
}

int Box::getnbCustomerNotAffected() const
{
  return nbCustomerNotAffected_;
}

int Box::getNbFacilityOpen() const
{
  int ret = 0;
  for(unsigned int i = 0; i < data_.getnbFacility(); ++i)
    {
      if(isOpened(i))
	{
	  ret++;
	}
    }
  return ret;
}

bool Box::getHasNeighbor() const
{
  return hasNeighbor_;
}

bool Box::getHasMoreStepWS() const
{
  return hasMoreStepWS_;
}

Data& Box::getData() const
{
  return data_;
}

void Box::setId(string s)
{
  id_ += s;
}

void Box::setMinZ1(double v)
{
  minZ1_ = v;
}
void Box::setMinZ2(double v)
{
  minZ2_ = v;
}
void Box::setMaxZ1(double v)
{
  maxZ1_ = v;
}
void Box::setMaxZ2(double v)
{
  maxZ2_ = v;
}

void Box::setHasNeighbor(bool b)
{
  hasNeighbor_ = b;
}

void Box::setHasMoreStepWS(bool b)
{
  hasMoreStepWS_ = b;
}

void Box::computeBox()
{
  //Calcul of the box
  for(unsigned int i = 0; i < data_.getnbCustomer(); ++i)
    {
      double vMinZ1 = DBL_MAX;
      double vMaxZ1 = -1;
      double vMinZ2 = DBL_MAX;
      double vMaxZ2 = -1;
      int iMinZ1 = -1, iMinZ2 = -1;
      for(unsigned int j = 0; j < data_.getnbFacility(); ++j)
	{
	  //Search for local min and max
	  if(facility_[j])
	    {
	      if( data_.getAllocationObj1Cost(i,j) <  vMinZ1 || 
		  (data_.getAllocationObj1Cost(i,j) == vMinZ1 && 
		   data_.getAllocationObj2Cost(i,j) < vMaxZ2) )
		{
		  // <Z1 || =Z1 et <Z2
		  vMinZ1 = data_.getAllocationObj1Cost(i,j);
		  vMaxZ2 = data_.getAllocationObj2Cost(i,j);
		  iMinZ1 = j;
		}
	      if(data_.getAllocationObj2Cost(i,j) <  vMinZ2 || 
		 (data_.getAllocationObj2Cost(i,j) == vMinZ2 && 
		  data_.getAllocationObj1Cost(i,j) < vMaxZ1) )
		{
		  // <Z2 || =Z2 et <Z1
		  vMinZ2 = data_.getAllocationObj2Cost(i,j);
		  vMaxZ1 = data_.getAllocationObj1Cost(i,j);
		  iMinZ2 = j;
		}
	    }
	}
      //If they are equals, this allocation is optimal <=> "trivial"
      if(iMinZ1 == iMinZ2)
	{
	  minZ1_ += data_.getAllocationObj1Cost(i,iMinZ1);
	  maxZ1_ += data_.getAllocationObj1Cost(i,iMinZ1);
	  originZ1_ += data_.getAllocationObj1Cost(i,iMinZ1);
	  minZ2_ += data_.getAllocationObj2Cost(i,iMinZ1);
	  maxZ2_ += data_.getAllocationObj2Cost(i,iMinZ1);
	  originZ2_ += data_.getAllocationObj2Cost(i,iMinZ1);
	  nbCustomerNotAffected_--;
	  isAssigned_[i] = true;
	}
      else
	//We add the lexicographically optimal cost
	{
	  minZ1_ += vMinZ1;
	  minZ2_ += vMinZ2;
	  maxZ1_ += vMaxZ1;
	  maxZ2_ += vMaxZ2;	
	}
    }
  if(nbCustomerNotAffected_ == 0)
    {
      //If all customers are affected, the box is a point, so there is no more WS step possible
      hasMoreStepWS_= false;
    }
}

void Box::openFacility(int fac)
{
  facility_[fac] = true;
  //We add costs to the box
  minZ1_ += data_.getFacility(fac).getLocationObj1Cost();
  maxZ1_ += data_.getFacility(fac).getLocationObj1Cost();
  originZ1_  += data_.getFacility(fac).getLocationObj1Cost();
  minZ2_ += data_.getFacility(fac).getLocationObj2Cost();
  maxZ2_ += data_.getFacility(fac).getLocationObj2Cost();
  originZ2_  += data_.getFacility(fac).getLocationObj2Cost();
}

void Box::print()
{
#ifdef verbose
  cout << "minZ1_ =" << minZ1_ << endl;
  cout << "minZ2_ =" << minZ2_ << endl;
  cout << "maxZ1_ =" << maxZ1_ << endl;
  cout << "maxZ2_ =" << maxZ2_ << endl;
  cout << "originZ1_ =" << originZ1_ << endl;
  cout << "originZ2_ =" << originZ2_ << endl;
  for(unsigned int i = 0; i < data_.getnbCustomer(); ++i)
    {
      if( !isAssigned_[i] )
	{
	  cout << "Customer: " << i << endl;
	  for(unsigned int j = 0; j < data_.getnbFacility(); ++j)
	    {
	      if( isOpened(j) )
		{
		  cout <<data_.getAllocationObj1Cost(i,j) <<"-";
		}
	    }
	  cout << endl;
	  for(unsigned int j = 0; j < data_.getnbFacility(); ++j)
	    {
	      if( isOpened(j) )
		{
		  cout <<data_.getAllocationObj2Cost(i,j) <<"-";
		}
	    }
	  cout <<endl;
	}
    }
#endif
}

//***** PUBLIC FONCTIONS *****

bool isDominatedBetweenTwoBoxes(Box *box1, Box *box2)
{
  bool dominated(false);
	
  if(	( box1->getMinZ1() > box2->getMaxZ1() && box1->getMinZ2() > box2->getMinZ2() ) || ( box1->getMinZ2() > box2->getMaxZ2() && box1->getMinZ1() > box2->getMinZ1() ) )
    {
      dominated = true;
    }
	
  return dominated;
}

bool isDominatedBetweenOrigins(Box *box1, Box *box2)
{
  bool dominated(false);
  if(	( box1->getOriginZ1() > box2->getMaxZ1() && box1->getOriginZ2() > box2->getMinZ2() ) || ( box1->getOriginZ2() > box2->getMaxZ2() && box1->getOriginZ1() > box2->getMinZ1() ) )
    {
      dominated = true;
    }
	
  return dominated;
}

void filterDominatedBoxes(vector<Box*> &vectBox)
{
  for(unsigned int it = 0; it < vectBox.size(); it++)
    {
      for(unsigned int it2 = it + 1; it2 < vectBox.size(); it2++)
	{
	  if( isDominatedBetweenTwoBoxes( vectBox[it2] , vectBox[it] ) )
	    {
	      //it2 is dominated
	      delete (vectBox[it2]);
	      vectBox.erase((vectBox.begin())+=it2);
	      it2--;//We delete it2, so we shift by one
	    }
	  else
	    {
	      if( isDominatedBetweenTwoBoxes( vectBox[it] , vectBox[it2] ) )
		{
		  //it is dominated
		  delete (vectBox[it]);
		  vectBox.erase((vectBox.begin())+=it);
		  //Delete it, pass to the next loop. Initialize it2 to it+1
		  it2 = it;
		}
	    }
	}
    }
}

bool isDominatedByItsOrigin(vector<Box*> &vectBox, Box *box)
{
  bool isDominated(false);
  vector<Box*>::iterator it;
  /*Stop Criterion
    - all the vector is travelled (but condition 3 may occur before)
    - we are dominated
    - we compare with itself
  */
  for( it = vectBox.begin(); it != vectBox.end() && !isDominated && (*it != box); it++)
    {
      if( isDominatedBetweenOrigins( box , (*it) ) )
	{
	  isDominated = true;
	}
    }
  return isDominated;
}

bool isDominatedByItsBox(vector<Box*> &vectBox, Box *box)
{
  bool isDominated(false);
  vector<Box*>::iterator it;
  /*Stop Criterion
    - all the vector is travelled (but condition 3 may occur before)
    - we are dominated
    - we compare with itself
  */
  for(it = vectBox.begin(); it != vectBox.end() && !isDominated && (*it != box); it++)
    {
      if( isDominatedBetweenTwoBoxes( box , (*it) ) )
	{
	  isDominated = true;
	}
    }	
  return isDominated;
}
