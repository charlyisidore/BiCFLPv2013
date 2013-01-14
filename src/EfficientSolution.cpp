#include "EfficientSolution.hpp"
#include <vector>

EfficientSolution::EfficientSolution()
{
  _X_e= std::vector<Solution*>();
}


std::vector<Solution*> EfficientSolution::X_e() const
{
  return _X_e;
}
bool EfficientSolution::addSolution(Solution* s)
{
	
  unsigned int it=0;
  bool s_non_dominated=true;
	
  std::vector<Solution*> res= std::vector<Solution*>();
  while(it < _X_e.size() && s_non_dominated){
    /* We take the maximum set of Xe  => to change it put : _
     * X_e[it]<=s || _X_e[it]==s
     */
    if( (*_X_e[it]) <= (*s) || (*_X_e[it]) == (*s)) 
      {
	s_non_dominated=false;
	//delete(s);		
      }		
    else if(!((*s)<=(*_X_e[it])))
      {
	res.push_back(_X_e[it]);		
      }
    else
      {
	//delete(_X_e[it]);
      }
    it++;
  }
  if(s_non_dominated)
    {
      _X_e = res;
      _X_e.push_back(s);
    }

  return s_non_dominated;
	
}

unsigned int EfficientSolution::size() const
{
  return  _X_e.size();
}


EfficientSolution::~EfficientSolution()
{
  for(unsigned int it=0; it <_X_e.size(); it++)
    {
      delete(_X_e[it]);
    }
}

Solution * EfficientSolution::operator[](unsigned int index)
{
  return _X_e[index];
}
