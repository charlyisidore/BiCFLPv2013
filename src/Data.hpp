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
* \file Data.hpp
* \brief Class of the \c Data.
* \author Salim BOUROUGAA & Alban DERRIEN & Axel GRIMAULT & Xavier GANDIBLEUX & Anthony PRZYBYLSKI
* \date 28 August 2012
* \version 1.1
* \copyright GNU General Public License 
*
* This class will contains all the values, parameters of the instance. Especially, it contains the allocation cost between customers and facilities.
*
*/

#ifndef DATA_H
#define DATA_H

#include "Facility.hpp"
#include "Customer.hpp"

#include <iostream>
#include <vector>
#include <cfloat>

/*! \namespace std
* 
* Using the standard namespace std of the IOstream library of C++.
*/
using namespace std;

/*! \class Data
* \brief Class to represent a \c Data.
*
*  This class represents a \c Data with all its attributes, parameters.
*/
class Data
{
public:
	/*! \typedef vector<Facility> ListFacilities
	*  \brief The list of all facilities.
	*
	* This is a vector from the STL Containers of object \c Facility.
	*/
    typedef vector<Facility> ListFacilities;
    /*! \typedef vector<Customer> ListCustomers
	*  \brief The list of all customers.
	*
	* This is a vector from the STL Containers of object \c Customer.
	*/
    typedef vector<Customer> ListCustomers;
    
	/*!
	*	\brief Constructor of the class \c Data.
	*
	*	\param[in] nbFacility : The number of \c Facility of the instance.
	*	\param[in] nbCustomer : The number of \c Customer of the instance.
	*	\param[in] name : The name of the instance.
	*/
    Data(unsigned int nbFacility, unsigned int nbCustomer, string name);
	/*!
	*	\brief Destructor of the class \c Data.
	*/
    ~Data();
    
    /*!
	*	\brief Method to add a \c Facility to the \c Data.
	*	\param fac : An object \c Facility.
	*/
    void addFacility(Facility fac);
    /*!
	*	\brief Method to add a \c Customer to the \c Data.
	*	\param cust : An object \c Customer.
	*/
    void addCustomer(Customer cust);
    /*!
	*	\brief Getter for the number of facilities.
	*	\return An unsigned int as the number of facilities of the instance.
	*/
    unsigned int getnbFacility() const;
	/*!
	*	\brief Getter for the number of customers.
	*	\return An unsigned int as the number of customers of the instance.
	*/
    unsigned int getnbCustomer() const;
	/*!
	*	\brief Getter for the sum of customers demands.
	*	\return A double as the sum of demands of customers of the instance.
	*/
    double getTotalDemand() const;
    /*!
   *	\brief Setter for the total demand of \c Customer.
   *	\param[in] val : A double which represents the value of the sum of all \c Customer demand.
   */
  void setTotalDemand(double val);

  

	/*!
	*	\brief Getter for the allocation cost w.r.t. objective 1 between a \c Customer and a \c Facility.
	*	\param[in] cust : The index of the \c Customer.
	*	\param[in] fac : The index of the \c Facility.
	*	\return A double as the value of the allocation cost w.r.t. objective 1 for the \c Customer cust to the \c Facility fac.
	*/
    double getAllocationObj1Cost(int cust, int fac) const;
    /*!
	*	\brief Getter for the allocation cost w.r.t. objective 2 between a \c Customer and a \c Facility.
	*	\param[in] cust : The index of the \c Customer.
	*	\param[in] fac : The index of the \c Facility.
	*	\return A double as the value of the allocation cost w.r.t. objective 2 for the \c Customer cust to the \c Facility fac.
	*/
    double getAllocationObj2Cost(int cust, int fac) const;
    /*!
	*	\brief Getter for a \c Facility.
	*	\param[in] fac : The index of the \c Facility to return.
	*	\return A \c Facility.
	*/
    Facility & getFacility(int fac);
      /*!
	*	\brief Getter for a \c Customer.
	*	\param[in] cust : The index of the \c Customer to return.
	*	\return A \c Customer.
	*/
    Customer & getCustomer(int cust);

    /*!
	*	\brief Getter for the name of the instance.
	*	\return A string which represents the name of the instance.
	*/
    string getFileName() const;
    
    /*!
	*	\brief Setter for the allocation cost w.r.t. objective 1 between a \c Customer and a \c Facility.
	*	\param[in] cust : The index of the \c Customer.
	*	\param[in] fac : The index of the \c Facility.
	*	\param[in] val : The value of the allocation cost of the customer cust to the facility fac w.r.t. objective 1.
	*/
    void setAllocationObj1Cost(int cust,int fac, double val);
    /*!
	*	\brief Setter for the allocation cost w.r.t. objective 2 between a \c Customer and a \c Facility.
	*	\param[in] cust : The index of the \c Customer.
	*	\param[in] fac : The index of the \c Facility.
	*	\param[in] val : The value of the allocation cost of the customer cust to the facility fac w.r.t. objective 2.
	*/
    void setAllocationObj2Cost(int cust, int fac, double val);
    /*!
	*	\brief Setter for the name of the instance.
	*	\param[in] name : A string which represents the name of the instance.
	*/
    void setFileName(string name);
    
private:
    ListFacilities facilityList_;
    ListCustomers customerList_;
  double total_demand_;
    string fileName_;/*!< A string which represents the name of the instance */
    double **allocationObj1Cost_;/*!< An array of double (2 dimensions) which represents the matrix of allocation cost w.r.t. objective 1 */
    double **allocationObj2Cost_;/*!< An array of double (2 dimensions) which represents the matrix of allocation cost w.r.t. objective 2 */
};

#endif
