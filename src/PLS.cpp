
#include "PLS.hpp"


/**
 * \fn localSearch(EfficientSolution & efficient_sol, Solution* s, Data & data)
 * \brief computes a neighborhood of the solutions s and updates the efficient solutions list
 * \param efficient_sol is the list of efficient solutions found until now
 * \param s the solution for which the neighborhood will be computed
 * \param data contains the problem data
 * \return does the function find new efficient solutions or not?
 */
bool localSearch1opt(EfficientSolution & efficient_sol, Solution* s, Data & data){
	
  bool useful =false;
  unsigned int numberOfFacility= data.getnbFacility();
  unsigned int numberOfCustomers= data.getnbCustomer();

  // one opt
  for (unsigned int i=0; i < numberOfCustomers; i++){
    vector<int> current_affectation;
    vector<bool> current_opened_facility;
    vector<double> current_residual_capacity;

    for (unsigned int j=0; j<numberOfCustomers; ++j)
      {
	current_affectation.push_back(s->getAffectation(j));
      }
    for (unsigned int j=0; j<numberOfFacility; ++j)
      {
	current_opened_facility.push_back((s->getY_j()[j] == '1') ? true : false);
      }
    for (unsigned int j=0; j<numberOfFacility; ++j)
      {
	current_residual_capacity.push_back(s->getResidualCapacity(j));
      }
    /* //debug
	cout<< "/////////////////////////////////"<<endl;
	cout << s <<endl;
	cout<< "/////////////////////////////////"<<endl;
	*/
    // try to find a facility (opened or nor) which is capable to serve the customer "i"
    for(unsigned int f=0; f < numberOfFacility; f++){
      if((f != (unsigned int)current_affectation[i]) && 
	 (current_residual_capacity[f] >= data.getCustomer(i).getDemand())){
		 /* // debug
		 cout<<"customer "<< i<< " facility "<< f<<endl;
			*/
	int old_facility= current_affectation[i];
	int new_facility= f;
	// TODO
	current_affectation[i]=new_facility;
	
	//compute the current residue-capacity
	current_residual_capacity[new_facility] -= data.getCustomer(i).getDemand();
	current_residual_capacity[old_facility] += data.getCustomer(i).getDemand();
	
	//we need to close old facility if it does not serve a customer
	current_opened_facility[new_facility]=true;
	current_opened_facility[old_facility]=false;
	// if there is at least one customer deserved by it, then it must be opened
	for(unsigned int c=0; c<numberOfCustomers;c++){
	  if(current_affectation[c] == old_facility){
	    current_opened_facility[old_facility] = true;
	    break;
	  }
	}
	//neighbor is always feasible
	Solution* neighbor = new Solution(current_affectation, 
					  current_opened_facility, 
					  data,
					  current_residual_capacity);
	/* // debug
	for(unsigned int alpha=0;alpha<current_affectation.size();alpha++){
		cout<<current_affectation[alpha] <<" ";
	}
		cout<< "\n neighbor"<<endl;
	cout << neighbor <<endl;
	*/
	// it should compute the objective functions
	// TODO evaluate th solution neighbor if not automatically done
	bool neighborIsEfficient = efficient_sol.addSolution(neighbor);
	if(neighborIsEfficient){
	  useful=true;
	}
	// TODO
	else{
		delete(neighbor);
	}
      }
    }
  }
  return useful;
}

bool localSearchSwap(EfficientSolution & efficient_sol, Solution* s, Data & data){
	
  bool useful = false;
  unsigned int numberOfFacility= data.getnbFacility();
  unsigned int numberOfCustomers= data.getnbCustomer();

  // swap
  for (unsigned int i=0; i < numberOfCustomers-1; i++){
    for (unsigned int j=i+1; j < numberOfCustomers; j++){
      vector<int> current_affectation;
      vector<bool> current_opened_facility;
      vector<double> current_residual_capacity;

      for (unsigned int k=0; k<numberOfCustomers; ++k)
	{
	  current_affectation.push_back(s->getAffectation(k));
	}
      for (unsigned int k=0; k<numberOfFacility; ++k)
	{
	  current_opened_facility.push_back((s->getY_j()[k] == '1') ? true : false);
	}
      for (unsigned int k=0; k<numberOfFacility; ++k)
	{
	  current_residual_capacity.push_back(s->getResidualCapacity(k));
	}

      unsigned int old_facility_i = current_affectation[i];
      unsigned int old_facility_j = current_affectation[j];
      // TODO
      current_affectation[i]=old_facility_j;
      current_affectation[j]=old_facility_i;
      
      if (old_facility_i != old_facility_j)
	{
	  current_residual_capacity[old_facility_i] = current_residual_capacity[old_facility_i] + 
	    data.getCustomer(i).getDemand() - data.getCustomer(j).getDemand();
	  current_residual_capacity[old_facility_j] = current_residual_capacity[old_facility_j] - 
	    data.getCustomer(i).getDemand() + data.getCustomer(j).getDemand();
	  if (current_residual_capacity[old_facility_i] >= 0  && current_residual_capacity[old_facility_j] >= 0)
	    {
	      Solution* neighbor = new Solution(current_affectation, 
						current_opened_facility, 
						data,
						current_residual_capacity);
	      // it should compute the objective functions
	      // TODO evaluate th solution neighbor if not automatically done
	      bool neighborIsEfficient = efficient_sol.addSolution(neighbor);
	      if(neighborIsEfficient){
		useful=true;
	      }
	      // TODO
		  else{
			delete(neighbor);
		  }

	    }
	}
    }
  }
  return useful;
}


/*
 * Too slow, don't using for many times 
 * 
 */
bool localSearch2opt(EfficientSolution & efficient_sol, Solution* s, Data & data){
	
  bool useful = false;
  unsigned int numberOfFacility= data.getnbFacility();
  unsigned int numberOfCustomers= data.getnbCustomer();
  // swap
  for (unsigned int i=0; i < numberOfCustomers-1; i++){
    for (unsigned int j=i+1; j < numberOfCustomers; j++){      
      for(unsigned int fi=0; fi<numberOfFacility; fi++){
	for(unsigned int fj=fi+1; fj<numberOfFacility; fj++){
	  if (fi != (unsigned int)s->getAffectation(i) && fj != (unsigned int)s->getAffectation(j) &&	// done in 1opt
	  		fi != (unsigned int)s->getAffectation(j) && fj != (unsigned int)s->getAffectation(i) && // done in swap
			s->getResidualCapacity(fi) - data.getCustomer(i).getDemand() >=0 && //solutions are not feasible
			s->getResidualCapacity(fj) - data.getCustomer(j).getDemand() >=0 )  //solutions are not feasible
	    {

	      vector<int> current_affectation;// = s->getAffectation();
	      vector<bool> current_opened_facility;
	      vector<double> current_residual_capacity;// = s->getResidualCapacity();
	      
	      for (unsigned int k=0; k<numberOfCustomers; ++k)
		{
		  current_affectation.push_back(s->getAffectation(k));
		}
		for (unsigned int k=0; k<numberOfFacility; ++k)
		{
		  current_residual_capacity.push_back(s->getResidualCapacity(k));
		}
	      for (unsigned int k=0; k<numberOfFacility; ++k)
		{
		  current_opened_facility.push_back((s->getY_j()[k] == '1') ? true : false);
		}
	      
	      unsigned int old_facility_i = current_affectation[i];
	      unsigned int old_facility_j = current_affectation[j];
	      
	      // TODO
	      current_affectation[i]=fi;
		  current_affectation[j]=fj;
		  
	      current_residual_capacity[old_facility_i] += data.getCustomer(i).getDemand();
	      current_residual_capacity[old_facility_j] += data.getCustomer(j).getDemand();
	      current_residual_capacity[fi] -= data.getCustomer(i).getDemand();
	      current_residual_capacity[fj] -= data.getCustomer(j).getDemand();
		

		  for(unsigned int c=0; c<numberOfCustomers; c++){
		    current_opened_facility[current_affectation[c]] = true;
		  }
		  Solution* neighbor = new Solution(current_affectation, 
						    current_opened_facility, 
						    data,
						    current_residual_capacity);
		  // it should compute the objective functions
		  // TODO evaluate th solution neighbor if not automatically done
		  bool neighborIsEfficient = efficient_sol.addSolution(neighbor);
		  if(neighborIsEfficient){
		    useful=true;
		  }
		  // TODO
		  else{
			delete(neighbor);
		  }

	    }
	}
      }
    }
  }
  return useful;
}



/**
 * \fn paretoLocalSearch(EfficientSolution & efficient_sol, Data & data, int nbboxes, int nbIteration)
 * \brief recursive methode of local search on the found efficient solutions
 * \param efficient_sol is the list of efficient solutions found until now
 * \param nbBoxes is the number of solutions on the efficient solutions list, for which the neighborhood will be computed
 * \param nbIteration is the maximal time number of the recursive call for this routine
 * \param data contains the problem data
 */
void paretoLocalSearch(EfficientSolution & efficient_sol, unsigned int nbBoxes, int nbIteration, Data & data)
{
  // TODO
  gnuplotPLS = true;
  ToFile::gnuplot_interactive(efficient_sol.X_e());
  for(int iterations = 0; iterations < nbIteration; iterations++){
    vector<Solution*> current_pareto_front;
    unsigned int nb=nbBoxes;
    for (unsigned int i=0; i<efficient_sol.size(); ++i)
      {
	current_pareto_front.push_back(efficient_sol[i]);
      }
    // "useful" informs us if the pls prings new efficient solutions
    bool useful=false;
    sort(current_pareto_front.begin(), 
	 current_pareto_front.end(), 
	 z1_solution1_lower_than_solution_2);
    if (nb > current_pareto_front.size())
      nb = current_pareto_front.size();
    // to define to the index of the next solution to study
    int step = current_pareto_front.size() / nb;
    //printf("%d", iterations);
    for(unsigned int i=0; i < current_pareto_front.size(); i+=step){
      // call of local search on selected solution
      bool modification1= localSearchSwap(efficient_sol, current_pareto_front[i], data);
      ToFile::gnuplot_interactive(efficient_sol.X_e());
      bool modification2= localSearch1opt(efficient_sol, current_pareto_front[i], data);
      ToFile::gnuplot_interactive(efficient_sol.X_e());
      bool modification3= false;
      if (Argument::two_opt) {
      	modification3= localSearch2opt(efficient_sol, current_pareto_front[i], data);
      	ToFile::gnuplot_interactive(efficient_sol.X_e());
      }	
      if(modification1 || modification2 || modification3){
			useful=true;
			
			//cout << i<<" is succed"<< endl;
		}
    }
    
    // debug: to see the evolution of the pareto during the PLS
    std::stringstream sstm2;
    sstm2 << "PopulationPLS_" << iterations;
    ToFile::savePopulation(efficient_sol.X_e(), data, sstm2.str().c_str());
    
    if(!useful){
	  // we stop the algorithme
      break;
    }
  }
}
