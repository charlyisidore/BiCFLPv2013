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
 
#include "Data.hpp"

Data::Data(unsigned int nbFacility, unsigned int nbCustomer, string name)
{
	allocationObj1Cost_ = new double*[nbCustomer];
	allocationObj2Cost_ = new double*[nbCustomer];
	for(unsigned int i = 0; i < nbCustomer; ++i)
	{
		allocationObj1Cost_[i] = new double[nbFacility];
		allocationObj2Cost_[i] = new double[nbFacility];
	}
	
	fileName_ = name;
	int index1 = int(fileName_.find('/'));
	int index2 = int(fileName_.find('.'));
	fileName_ = name.substr(index1 + 1, index2 - index1 - 1);
}

Data::~Data()
{
	for(unsigned int i = 0; i < getnbCustomer(); ++i)
	{
		delete[] allocationObj1Cost_[i];
		delete[] allocationObj2Cost_[i];
	}
	delete[] allocationObj1Cost_;
	delete[] allocationObj2Cost_;
}

void Data::addFacility(Facility fac)
{
	facilityList_.push_back(fac);
}

void Data::addCustomer(Customer cust)
{
	customerList_.push_back(cust);
}

unsigned int Data::getnbFacility() const
{
	return facilityList_.size();
}

unsigned int Data::getnbCustomer() const
{
	return customerList_.size();
}

double Data::getAllocationObj1Cost(int cust, int fac) const
{
	return allocationObj1Cost_[cust][fac];
}

double Data::getAllocationObj2Cost(int cust, int fac) const
{
	return allocationObj2Cost_[cust][fac];
}

Facility & Data::getFacility(int fac)
{
	return facilityList_[fac];
}

Customer & Data::getCustomer(int cust)
{
	return customerList_[cust];
}


string Data::getFileName() const
{
	return fileName_;
}

void Data::setAllocationObj1Cost(int cust,int fac, double val)
{
	allocationObj1Cost_[cust][fac] = val;
}

void Data::setAllocationObj2Cost(int cust,int fac, double val)
{
	allocationObj2Cost_[cust][fac] = val;
}

void Data::setFileName(string name)
{
	fileName_ = name;
}


double Data::getTotalDemand() const
{
  return total_demand_;
}

void Data::setTotalDemand(double val)
{
  total_demand_ = val;
}
