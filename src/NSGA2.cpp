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

#include "NSGA2.hpp"
#include <sstream>
bool z1_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2)
{
  return ((*sol1).getObj1() < (*sol2).getObj1()) || 
    ((*sol1).getObj1() == (*sol2).getObj1() && (*sol1).getObj2() < (*sol2).getObj2());
}

bool z2_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2)
{
  return ((*sol1).getObj2() < (*sol2).getObj2()) || 
    ((*sol1).getObj2() == (*sol2).getObj2() && (*sol1).getObj1() < (*sol2).getObj1());
}

bool crowding_solution1_lower_than_solution_2(Solution * sol1, Solution * sol2)
{
  return ((*sol1).rank() < (*sol2).rank()) || 
    ((*sol1).rank() == (*sol2).rank() && (*sol1).kappa() > (*sol2).kappa());
}

Solution * tournament(Solution * father1, Solution * father2)
{
  Solution * result_of_battle;
  if(father1->rank() < father2->rank()){
    result_of_battle = father1;
  }
  else if(father1->rank() > father2->rank()){
    result_of_battle = father2;
  }
  else { // father1->rank() == father2->rank()
    if(father1->kappa() > father2->kappa()){
      result_of_battle = father1;
    }
    else if(father1->kappa() < father2->kappa()){
      result_of_battle = father2;
    }
    else { // father1->kappa() == father2->kappa()
      result_of_battle = (frandAB(0,1) < 0.5) ? father1 : father2;
    }
  }
  return result_of_battle;
}


unsigned int ranking(std::vector<Solution*> &population){
  for(unsigned int i = 0; i<population.size(); i++){
    (population[i])->setRank(0);
  }	
  unsigned int rank = 1;
  bool all_solutions_ranked = false;
  unsigned int solutions_already_ranked = 1;
  while(all_solutions_ranked == false){
    for(unsigned int i = 0; i<population.size(); i++){
      if(population[i]->not_yet_ranked()){
	/* we are going to check that a solution (population[i]) is not dominated by 
	 * not yet ranked solutions.
	 * if it is not dominated, then we initialize its rank
	 */
	bool dominated = false;
	for(unsigned int j = 0; j<population.size(); j++){
	  if(((*(population[j])) <= (*(population[i]))) && 
	     ((population[j]->rank() == rank) || (population[j]->not_yet_ranked()))){
	    dominated = true;
	    break;
	  }
	}
	/* dominated == false, so no solution (not yet ranked) dominates population[i]
	 */
	if(dominated == false){
	  population[i]->setRank(rank);
	}
      }
    }
    all_solutions_ranked = true;
    if (solutions_already_ranked == population.size()){
      all_solutions_ranked = false;
    }
    // check that all solutions are ranked    
    for(unsigned int i = 0; i<population.size(); i++){ // not population.size() but ceil(population.size()/2)+1
      if((population[i])->not_yet_ranked() || 
	 (population[population.size() - 1 - i ])->not_yet_ranked()){
	all_solutions_ranked = false;
	break;
      }
    }
    
    rank++;
  }
  return rank - 1;
}

void crowding (std::vector<Solution*> &population){
  unsigned int population_size = population.size();
  unsigned int max_rank = ranking(population);  // this line is compulsory for the rest of crowding algorithm

  std::vector < std::vector<Solution *> > ordered_ranked_population = std::vector <std::vector<Solution *> >();
  // creation of lists ordered in function of their ranks			
  for(unsigned int i = 0; i < max_rank; i++){
    std::vector<Solution*> tmp = std::vector<Solution *>();
    ordered_ranked_population.push_back(tmp);
  }
  // put in i° list the solution of rank i
  for(unsigned int i = 0; i < population_size ; i++){
    ordered_ranked_population[(*(population[i])).rank() - 1].push_back(population[i]); 
  }

  for(unsigned int i = 0; i < max_rank; i++){
    sort((ordered_ranked_population[i]).begin(), (ordered_ranked_population[i]).end(), z1_solution1_lower_than_solution_2);
  }
  
  for(unsigned int i = 0; i < max_rank; i++){

    Solution * first = ((ordered_ranked_population[i])[0]);
    (*first).setKappa(DIMENSION + 1);
    if((ordered_ranked_population[i]).size() > 1){
      Solution * last = (ordered_ranked_population[i])[(ordered_ranked_population[i]).size()-1];
      (*last).setKappa(DIMENSION + 1);
      double scale_z1 = (*last).getObj1() - (*first).getObj1();  //  Y_{1}^{A} - Y_{1}^{I}
      double scale_z2 = (*first).getObj2() - (*last).getObj2();  //  Y_{2}^{A} -  Y_{2}^{I}

      for(unsigned int j= 1; j < (ordered_ranked_population[i]).size()-1; j++){
	Solution * previous = (ordered_ranked_population[i])[j-1];
	Solution * current = (ordered_ranked_population[i])[j];
	Solution * next = (ordered_ranked_population[i])[j+1];
	(*current).setKappa((((*next).getObj1() - (*previous).getObj1()) / scale_z1) + (( (*previous).getObj2() - (*next).getObj2()) / scale_z2)) ;
      }
    }
  }
}


void initialization(EfficientSolution & efficient_population,
		    std::vector<Solution*> &population,  
		    unsigned int numberOfLambda,
		    std::vector<Box*> vectorBoxFinal,
		    Data & data)
{
  for(unsigned int i=0; i < vectorBoxFinal.size(); i++)
    {
      vector <bool> opened_facility;
      for(unsigned int j=0; j < data.getnbFacility(); j++)
	{
	  opened_facility.push_back(vectorBoxFinal[i]->y_j()[j]);
	}
      vector <Solution* >tmp_solutions = repare(data, 
						opened_facility, 
						numberOfLambda, 
						efficient_population);
      for(unsigned int s=0; s<tmp_solutions.size(); s++)
	population.push_back(tmp_solutions[s]);
    }
}

void  evolution (EfficientSolution & efficient_population, 
		 std::vector <Solution*> &population, 
		 std::vector <Solution*> &offspring_population, 
		 double P_c, 
		 double P_m,
		 Data & data)
{

  unsigned int population_size = population.size();
  unsigned int numberOfFacility = data.getnbFacility();
  unsigned int numberOfCustomers = data.getnbCustomer();
  
  while(offspring_population.size() < population_size)
    {
      // tournament n°1    
      Solution* father1 = population[randAB(0, population_size-1)];
      Solution* father2 = population[randAB(0, population_size-1)];
      Solution* result_of_battle_1 = tournament(father1, father2);
      // tournament n°2
      father1 = population[randAB(0, population_size-1)];
      father2 = population[randAB(0, population_size-1)];
      Solution* result_of_battle_2  = tournament(father1, father2);

      if(result_of_battle_1 != result_of_battle_2){
	// crossover
	double pcc=frandAB(0,1);
	if(pcc <= P_c)
	  {
	    std::vector<Solution*> path = path_relinking(data, result_of_battle_1,result_of_battle_2, efficient_population);
	    crowding(path); // this crowding function calls ranking function
	    sort(path.begin(), path.end(), crowding_solution1_lower_than_solution_2);

	    //note: path contains at least two solutions (solutions used to the path relinking)

	    // mutation
	    double pmc=frandAB(0,1);

	    if(pmc <= P_m)
	      {
		for(unsigned int elem=0;elem<2;elem++){
		  bool correct=true;
		  // mutation of element i
		  int position_mut= randAB(0, numberOfCustomers-1); //the position of the mutation
		  int new_facility = randAB(0,numberOfFacility-1); // ????
		  std::vector<int> tmp1= ((path[elem])->getAffectation());
		  std::vector<int> _affectation= std::vector<int>();
                  for(unsigned int m=0;m< numberOfCustomers; m++){
			_affectation.push_back(tmp1[m]);
		  }
		  int old_facility = _affectation[position_mut];
		  _affectation[position_mut]=new_facility;
		  std::vector<double> tmp2=((path[elem])->getResidualCapacity());
		  std::vector<double> _residue_capacity= std::vector<double>();
                  for(unsigned int m=0;m< numberOfFacility; m++){
			_residue_capacity.push_back(tmp2[m]);
		  }
		  _residue_capacity[new_facility] -= data.getCustomer(position_mut).getDemand();
		  _residue_capacity[old_facility] += data.getCustomer(position_mut).getDemand();
					
		  if(_residue_capacity[new_facility] < 0){
		    correct = false;
		  }
					
		  //does the facility close or note?
		  std::vector<bool> opened_facility;
		  for (unsigned int i=0; i<numberOfFacility; ++i)
		    {
		      if((path[elem])->getY_j()[i] == '1')
			opened_facility.push_back(true);
		      else
			opened_facility.push_back(false);
		    } 
		  opened_facility[new_facility]=true;
		  opened_facility[old_facility]=false;
		  // if there is other custemers deserved by it => then it still open
		  for(unsigned int c=0; c<numberOfCustomers;c++){
		    if(_affectation[c] == old_facility){
		      _affectation[old_facility] = true;
		      break;
		    }
		  }

		  Solution* mutated_element = new Solution(_affectation, 
							   opened_facility, 
							   data,
							   _residue_capacity);
		  // if the visited solution est feasible / then we add it to the path
		  if (mutated_element->isCorrect()){
		    offspring_population.push_back(mutated_element);
		    efficient_population.addSolution(mutated_element);
		  }
		  else{
			delete mutated_element;
		  }
		}
	      }
	  }
      }
    }
}


// evolutionary multiobjective algorithm
void nsga2(vector<Solution* > &initial_population,
		   EfficientSolution &efficient_population, 
		   unsigned int numberOfLambda,
		   std::vector<Box*> vectorBoxFinal,
		   double P_c,
		   double P_m,
		   unsigned int nGenerations,
		   Data & data)
{		
  srand((unsigned)time(0)); 
  std::vector <Solution*> population = std::vector<Solution*>();
  // Generate an initial population of nIndividuals
  initialization(efficient_population, population, numberOfLambda, vectorBoxFinal, data);
 /* 
  int affectation1[90]={1,1,1,1,1,20,20,1,1,20,1,1,20,1,1,1,1,1,1,1,2,2,20,2,1,1,1,1,2,2,13,3,0,1,1,16,19,28,0,19,29,18,12,14,29,0,16,13,24,28,0,18,16,24,3,3,12,14,29,29,0,12,4,19,1,21,14,26,21,12,12,0,0,14,29,0,29,26,3,5,7,22,19,8,18,18,0,9,10,4};

int affectation2[90]={1,1,1,1,1,20,20,20,1,1,1,20,1,1,1,1,1,1,1,1,2,2,1,1,2,1,2,1,1,2,8,8,5,25,9,16,14,27,0,13,25,18,26,3,23,19,6,10,6,24,22,9,18,1,16,26,16,14,28,23,27,21,1,21,28,21,8,22,0,22,19,12,17,10,25,3,18,3,3,18,7,3,16,8,18,16,0,9,14,4};
int affectation3[90]={1,1,1,20,20,1,20,1,1,1,1,1,20,1,1,1,1,1,1,1,2,2,1,1,1,1,2,1,2,2,13,8,0,25,8,16,19,24,0,12,29,8,26,14,29,19,16,13,24,16,0,18,21,24,16,23,12,14,23,29,0,12,21,21,15,21,14,26,16,12,18,0,9,19,25,26,21,15,3,16,7,25,19,8,18,16,0,1,10,4};

vector<int> affect1=vector<int>();
vector<int> affect2=vector<int>();
vector<int> affect3=vector<int>();

vector<bool> open_dep1=vector<bool>();
vector<bool> open_dep2=vector<bool>();
vector<bool> open_dep3=vector<bool>();
for(int i=0; i<30; i++){
		open_dep1.push_back(false);
		open_dep2.push_back(false);
		open_dep3.push_back(false);
}

vector<double> resid1=vector<double>();
vector<double> resid2=vector<double>();
vector<double> resid3=vector<double>();
for(int i=0; i<30; i++){
		resid1.push_back(data.getFacility(i).getCapacity());
		resid2.push_back(data.getFacility(i).getCapacity());
		resid3.push_back(data.getFacility(i).getCapacity());
}

for(int i=0; i<90; i++){
		affect1.push_back(affectation1[i]);
		affect2.push_back(affectation2[i]);
		affect3.push_back(affectation3[i]);
		
		open_dep1[affectation1[i]]=true;
		open_dep2[affectation2[i]]=true;
		open_dep3[affectation3[i]]=true;
		
		resid1[affectation1[i]] -= data.getCustomer(i).getDemand();
		resid2[affectation2[i]] -= data.getCustomer(i).getDemand();
		resid3[affectation3[i]] -= data.getCustomer(i).getDemand();

}
Solution* sol1=new Solution(affect1,open_dep1, data,resid1);
Solution* sol2=new Solution(affect2,open_dep2,data,resid2);
Solution* sol3=new Solution(affect3,open_dep3,data,resid3);
population.push_back(sol1);
population.push_back(sol2);
population.push_back(sol3);
efficient_population.addSolution(sol1);
efficient_population.addSolution(sol2);
efficient_population.addSolution(sol3);
*/
  
  for(unsigned int i=0; i<population.size(); i++)
    initial_population.push_back(population[i]);
  ToFile::savePopulation(initial_population, data, "InitialPopulationNSGA");
  
  //ToFile::gnuplot_interactive(initial_population);
 


  for(unsigned int k=0; k<nGenerations; k++){
    std::vector <Solution*> offspring_population = std::vector<Solution*>();
    
    std::vector <Solution*> result_population = std::vector<Solution*>(); //will contain the current population and its offspring one
    
    crowding(population); // this crowding function calls ranking function
    // recombination, and mutation operators to create a offspring population 
    //   O_t of size nIndividuals 
    evolution(efficient_population, population, offspring_population, P_c, P_m, data);
	      
    for(unsigned int i = 0; i < population.size(); i++){
      result_population.push_back(population[i]);
    }

    for(unsigned int i = 0; i < offspring_population.size(); i++){
      result_population.push_back(offspring_population[i]);
    }

    crowding(result_population); // the crowding function calls ranking function

    sort(result_population.begin(), 
	 result_population.end(), 
	 crowding_solution1_lower_than_solution_2);
    //    std::cout << result_population.size() << std::endl;

    // we are sure that: result_population.size() >= population.size()
    for(unsigned int i=0; i<population.size(); i++){
      population[i]= result_population[i];
      result_population[i]=NULL; // in order to avoid the destruction of the solution.
    }
    
     // if you need to see the evolution of the population at each generation
    std::stringstream sstm2;
    sstm2 << "PopulationNSGA_" << k;
    ToFile::savePopulation(population, data, sstm2.str().c_str());
    ToFile::gnuplot_interactive(population);
  }
  ToFile::savePopulation(population, data, "FinalPopulationNSGA");
  
}
