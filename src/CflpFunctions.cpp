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

#include "CflpFunctions.hpp"


double randomGeneration(double X_MIN, double X_MAX)
{
  return frandAB(X_MIN,X_MAX+0.00000000001);
}

double frandAB(double a, double b){
     
  return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

int randAB(int a, int b){
  int n = b-a;
  int partSize   = 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1));
  int maxUsefull = partSize * n + (partSize - 1);
  int draw;
    
  do {
    draw = rand();
  } while (draw > maxUsefull);
  return a + (draw / partSize);
}



vector <Solution *> repare(Data &data,
			   vector<bool> & opened_facility, 
			   double numberOfLambda,
			   EfficientSolution & X_e
			   ){
  vector <  Solution* > corrected_solutions;
  double step= 1.0/(double)(numberOfLambda);
  unsigned int numberOfFacility= data.getnbFacility();
  unsigned int numberOfCustomers= data.getnbCustomer();

  for(double lambda=0.; lambda<= 1.; lambda += step){
    bool reparation_sucess=true;
      
    // starting of reparation procedure  
    // the following variable will contain the unused capacity of each facility at each moment
    vector<double> residue_capacity =vector<double>(); 
    // the following variable corresponds to each customer is affected to a facility
    vector< int > customer_i_is_affected_to_facility_value_at_i = vector<int >();  
    // initialization phase
    for (unsigned int i = 0; i < numberOfFacility; i++){
      residue_capacity.push_back(data.getFacility(i).getCapacity());
    }
          
    // if capacity permitts it
    for (unsigned int c=0; c<numberOfCustomers; c++){
      double dist_min = DBL_MAX;
      int facility_min=-1; // not succesful
      /* find the opened facility which both minimizes the service of this customer and
       * its capacity is greater than customer's demand
       */ 
      for (int f=0; f<(int)numberOfFacility; f++){
	if((opened_facility[f]) && 
	   (residue_capacity[f]-data.getCustomer(c).getDemand()  >= 0)){
	  double dist= lambda*data.getAllocationObj1Cost(c,f) + 
	    (1-lambda)* data.getAllocationObj2Cost(c,f);
	  if( dist < dist_min){
	    dist_min = dist;
	    facility_min=f;
	  }
	}
      }
      if(facility_min != -1){    // if success of affectation
	customer_i_is_affected_to_facility_value_at_i.push_back(facility_min);
	residue_capacity[facility_min] -= data.getCustomer(c).getDemand();
      }
      else{ // we should open a new facility
	int facility_to_open = -1;
	double cost_facility_to_open = DBL_MAX;
	/* find the closed facility whose opening cost is cheaper
	 */
	for (int f=0; f<(int)numberOfFacility; f++){
	  double facility_cost = lambda*data.getFacility(f).getLocationObj1Cost() +
	    (1-lambda)*data.getFacility(f).getLocationObj2Cost();
	  if((residue_capacity[f] - data.getCustomer(c).getDemand() >= 0) &&
	     (facility_cost < cost_facility_to_open))
	    {
	      facility_to_open = f;
	      cost_facility_to_open = facility_cost;
	    }
	}
	//we found an interesting facility to open 
	if(facility_to_open != -1){
	  customer_i_is_affected_to_facility_value_at_i.push_back(facility_to_open);
	  residue_capacity[facility_to_open] -= data.getCustomer(c).getDemand();
	  // we mark it as opened
	  opened_facility[facility_to_open]=true;
	}
	else{
	  // bug unuseful to correct
	  std::cout << "reparation failure with lambda = " << lambda << std::endl;
	  reparation_sucess=false;
	  break;
	}
      }
    }
    if(reparation_sucess){
      Solution* my_solution= new Solution(customer_i_is_affected_to_facility_value_at_i, 
					  opened_facility,
					  data,
					  residue_capacity);
      // add to the initial population	
      corrected_solutions.push_back(my_solution); 
      // add if possible to the non dominated points.
      X_e.addSolution(my_solution);  
    }
  }
  return corrected_solutions;
}

vector< Solution* > path_relinking( Data &data,
				    Solution* s1, 
				    Solution* s2, 
				    EfficientSolution & X_e)
{	
  unsigned int numberOfFacility = data.getnbFacility();
  unsigned int numberOfCustomers = data.getnbCustomer();
  vector<Solution*> path;
  vector<int> current_affectation;
  vector<bool> current_opened_facility;
  vector<double> current_residue_capacity;
  // initialization
  path.push_back(s1);
  path.push_back(s2);
  for (unsigned int i=0; i<numberOfCustomers; ++i)
    {
      current_affectation.push_back(s1->getAffectation(i));
    }
  for (unsigned int i=0; i<numberOfFacility; ++i)
    {
      current_opened_facility.push_back((s1->getY_j()[i] == '1') ? true : false);
    }
  for (unsigned int i=0; i<numberOfFacility; ++i)
    {
      current_residue_capacity.push_back(s1->getResidualCapacity(i));
    }

  for(unsigned int i=0; i<numberOfCustomers; i++){
    bool correct=true;
    if(current_affectation[i] != s2->getAffectation(i)){
      int old_facility = current_affectation[i];
      int new_facility = s2->getAffectation(i);
      current_affectation[i] = new_facility;
      //compute the current residue-capacity
      current_residue_capacity[new_facility] -= data.getCustomer(i).getDemand();
      current_residue_capacity[old_facility] += data.getCustomer(i).getDemand();
      if(current_residue_capacity[new_facility] < 0){
	correct = false;
      }
      //we need to close old facility if it does not serve a customer
      current_opened_facility[new_facility] = true;
      current_opened_facility[old_facility] = false;
      // if there is at least one customer deserved by it, then it must be opened
      for(unsigned int c=0; c<numberOfCustomers;c++){
	if(current_affectation[c] == old_facility){
	  current_opened_facility[old_facility] = true;
	  break;
	}
      }

      Solution* solution_in_path = new Solution(current_affectation, 
						current_opened_facility, 
						data,
						current_residue_capacity);
      // if this solution is feasible, then we add it in the path
      if (solution_in_path->isCorrect()){
	path.push_back(solution_in_path);
	X_e.addSolution(solution_in_path);
      }
    }
  }	
  return path;
}