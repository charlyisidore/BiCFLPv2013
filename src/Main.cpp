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
 * \file Main.cpp
 * \brief Main of the software.
 * \author Salim BOUROUGAA & Mohamed CISSE & Alban DERRIEN & Axel GRIMAULT & Xavier GANDIBLEUX & Takfarinas SABER & Anthony PRZYBYLSKI
 * \date 28 August 2012
 * \version 1.1
 * \copyright GNU General Public License
 *
 */

#include <sys/time.h>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <cfloat>
#include <cmath>
#include <cstdlib>

#include "Argument.hpp"
#include "Parser.hpp"
#include "Data.hpp"
#include "Functions.hpp"
#include "CflpFunctions.hpp"
#include "ToFile.hpp"
#include "EfficientSolution.hpp"
#include "NSGA2.hpp"
#include "PLS.hpp"

/*! \namespace std
 * 
 * Using the standard namespace std of the IOstream library of C++.
 */
using namespace std;

/*!
 *	\defgroup global Global Variables
 */

/*!
 *	\defgroup main Main
 */

/*!
 *	\var modeVerbose
 *	\ingroup global
 *	\brief Variable representing the Verbose mode.
 *
 *	This boolean gets the value TRUE if the verbose mode is on, and FALSE otherwise. If the verbose mode is on, the software prints detailled information while running.
 */
bool modeVerbose = false;
/*!
 *	\var modeExport
 *	\ingroup global
 *	\brief Variable representing the Export mode.
 *
 *	This boolean gets the value TRUE if the export mode is on, and FALSE otherwise. If the export mode is on, result files are written in the folder /res.
 */
bool modeExport = false;


FILE * gnuplot_fp = 0; // Gnuplot pipe
double minX = 0;
double minY = 0;
double maxX = 0;
double maxY = 0;
bool gnuplotPLS = false;
/*!
 *	\fn int main(int argc, char *argv[])
 *	\ingroup main
 *
 *	\brief This is the main of the software.
 *	\param[in] argc : An integer which represents the number of arguments passed to the line command.
 *	\param[in] argv : An array of character which represents all the arguments.
 */
int main(int argc, char *argv[])
{
  Data* data;//Data
	
  long int nbToCompute;
  long int nbWithNeighbor;
  long int nbSolLS(0);
  long int boxBeforeFitlering(0);
  long int boxAfterFiltering(0);
  long int boxAfterReconstruction(0);
  long int numberBoxComputed(0);
  long double boxTotal(0);

  //Time strucure
  struct timeval start, end, beginB, endB, beginBF, endBF, beginRC, endRC, beginNSGA, endNSGA, beginLS, endLS, beginPLS, endPLS;
    
  //## READING ARGUMENTS ##

  Argument::parse( argc, argv );

  if ( Argument::help )
    {
      Argument::usage( argv[0] );
      return 0;
    }
  else if ( Argument::filename.empty() )
    {
      std::cout << "Type for help : " << argv[0] << " --help" << std::endl;
      return 0;
    }

  if (Argument::verbose)
    {
      Argument::print();
    }
if ( Argument::capacitated )
{
	gnuplot_fp = popen("gnuplot -persist", "w");
}
  //## END READING ARGUMENTS ##

  data = Parser::Parsing(Argument::filename);
	
  if(Argument::mode_export)
    {
      ToFile::removeFiles();
      computeCorrelation(*data);
    }
	
  if(Argument::verbose)
    {
      cout << endl;
      cout << "+" << setfill('-') << setw(15) << "+" << " INSTANCE " << "+" << setw(16) << "+" << endl;
      cout << setfill (' ');
      cout << " " << setw(20) << left << "Name " << "|" << setw(20) << right << basename((char *)data->getFileName().c_str()) << " " << endl;
      cout << " " << setw(20) << left << "Facility " << "|" << setw(20) << right << data->getnbFacility() << " " << endl;
      cout << " " << setw(20) << left << "Customer " << "|" << setw(20) << right << data->getnbCustomer() << " " << endl;
      cout << " " << setw(20) << left << "Correlation " << "|" << setw(20) << right << computeCorrelation(*data) << " " << endl;
      cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
    }

  gettimeofday(&start,NULL);
	
  //#############################
  //## Functions to create Box ##
	
  boxTotal = pow((long double)2, (int)data->getnbFacility() )-1;
	
  vector<Box*> vectorBox;
	
  gettimeofday(&beginB,NULL);		
  numberBoxComputed = createBox(vectorBox, *data);		
  boxBeforeFitlering = vectorBox.size();		
  gettimeofday(&endB,NULL);
       
  if(Argument::verbose)
    {
      cout << "+" << setfill('-') << setw(18) << "+" << " BOX " << "+" << setw(18) << "+" << endl;
      cout << setfill (' ');
      cout << "+" << setfill(' ') << setw(10) << " " <<" ! before filtering ! " << " " << setw(9) << "+" << endl;
      cout << " " << setw(20) << left << "Box Total " << "|" << setw(20) << right << setprecision(0) << fixed << boxTotal << " " << endl;
      cout << " " << setw(20) << left << "Box Computed " << "|" << setw(20) << right << numberBoxComputed << " " << endl;
      cout << " " << setw(20) << left << "Box Non-Dominated" << "|" << setw(20) << right << boxBeforeFitlering << " " << endl;
      cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginB,endB) + time_ms_Diff(beginB,endB)) << " " << endl;
      cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
    }
	
  //##################################################
  //## Functions to filter Boxes and reconstruction ##
	
  vector<Box*> vectorBoxFinal;
	
  if(Argument::filtering)
    {
      gettimeofday(&beginBF,NULL);
      boxFiltering(vectorBox, *data, nbToCompute, nbWithNeighbor);
      gettimeofday(&endBF,NULL);
		
      boxAfterFiltering = vectorBox.size();	
			
      if(Argument::reconstruction)
	{
	  gettimeofday(&beginRC,NULL);
	  recomposition(vectorBox, vectorBoxFinal, *data, nbToCompute, nbWithNeighbor);
	  gettimeofday(&endRC,NULL);
	  boxAfterReconstruction = vectorBoxFinal.size();
	}
      else
	{
	  vectorBoxFinal = vectorBox;
	}
		
      if(Argument::verbose)
	{
	  cout << "+" << setfill('-') << setw(13) << "+" << " BOX FILTERING " << "+" << setw(13) << "+" << endl;
	  cout << setfill (' ');
	  cout << "+" << setfill(' ') << setw(10) << " " <<" ! after filtering !  " << " " << setw(9) << "+" << endl;
	  cout << " " << setw(20) << left << "Box " << "|" << setw(20) << right << setprecision(0) << fixed << boxAfterFiltering << " " << endl;
	  cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginBF,endBF) + time_ms_Diff(beginBF,endBF)) << " " << endl;
	  if(Argument::reconstruction)
	    {
	      cout << "+" << setfill(' ') << setw(8) << " " <<" ! after reconstruction !  " << " " << setw(6) << "+" << endl;
	      cout << " " << setw(20) << left << "Box " << "|" << setw(20) << right << setprecision(0) << fixed << boxAfterReconstruction << " " << endl;
	      cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginRC,endRC) + time_ms_Diff(beginRC,endRC)) << " " << endl;
	    }
	  cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
	}
	        
    }
  else
    {
      vectorBoxFinal = vectorBox;
    }

  if(!Argument::capacitated)
    {
      //###################
      //## LABEL SETTING ##
  
      list<Solution> allSolution;
      gettimeofday(&beginLS,NULL);  
      nbSolLS = runLabelSetting(vectorBoxFinal,*data, allSolution);
      gettimeofday(&endLS,NULL);

      if(Argument::verbose)
	{
	  cout << "+" << setfill('-') << setw(13) << "+" << " LABEL SETTING " << "+" << setw(13) << "+" << endl;
	  cout << setfill (' ');
	  cout << " " << setw(20) << left << "Sol computed " << "|" << setw(20) << right << setprecision(0) << fixed << nbSolLS << " " << endl;
	  cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginLS,endLS) + time_ms_Diff(beginLS,endLS)) << " " << endl;
	  cout << "+" << setfill('-') << setw(42) << "+" << endl;
	}

      //#######################################################
      //## END OF EXACT RESOLUTION FOR FLP WITHOUT CAPACITY  ##
       
      gettimeofday(&end,NULL);
      cout << endl;
      cout << "+" << setfill('-') << setw(15) << "+" << " SYNTHESIS " << "+" << setw(15) << "+" << endl;
      cout << setfill (' ');
      cout << " " << setw(20) << left << "Instance " << "|" << setw(20) << right << basename((char *)data->getFileName().c_str()) << " " << endl;
      cout << " " << setw(20) << left << "Solutions " << "|" << setw(20) << right << setprecision(0) << fixed << nbSolLS << " " << endl;
      cout << " " << setw(20) << left << "Total Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(start,end) + time_ms_Diff(start,end)) << " " << endl;
      cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
      
      if(Argument::mode_export)
	{
	  if( system("bash ./plot/plot.sh") != 0 )
	    {
	      cout << " Failure in the execution of the script " << endl;
	    }
	}
    }
  else
    {
      //############
      //## NSGA2  ##

      gettimeofday(&beginNSGA, NULL);
      vector<Solution* > initial_population;
      EfficientSolution efficient_solutions;
      nsga2(initial_population,
	    efficient_solutions, 
	    Argument::nb_lambda, 
	    vectorBoxFinal,
	    Argument::Pc,
	    Argument::Pm,
	    Argument::generations,
	    *data);
      gettimeofday(&endNSGA,NULL);

      cout << "+" << setfill('-') << setw(17) << "+" << " NSGA2 " << "+" << setw(17) << "+" << endl;
      cout << setfill (' ');
      cout << " " << setw(20) << left << "Box " << "|" << setw(20) << right << setprecision(0) << fixed << vectorBoxFinal.size() << " " << endl;
      cout << " " << setw(20) << left << "Initial Population " << "|" << setw(20) << right << setprecision(0) << fixed << initial_population.size() << " " << endl;
      cout << " " << setw(20) << left << "Efficient Solutions " << "|" << setw(20) << right << setprecision(0) << fixed << efficient_solutions.size() << " " << endl;
      cout << " " << setw(20) << left << "Generations " << "|" << setw(20) << right << setprecision(0) << fixed << Argument::generations << " " << endl;
      cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginNSGA,endNSGA) + time_ms_Diff(beginNSGA,endNSGA)) << " " << endl;
      cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
      if(Argument::pls)
	{
	  gettimeofday(&beginPLS,NULL);  
	  cout << "+" << setfill('-') << setw(18) << "+" << " PLS " << "+" << setw(18) << "+" << endl;
	  cout << setfill (' ');
	  paretoLocalSearch(efficient_solutions, Argument::pls_poll_points, Argument::pls_iterations, *data);
	  gettimeofday(&endPLS,NULL);
	  cout << " " << setw(20) << left << "Iterations " << "|" << setw(20) << right << setprecision(0) << fixed << Argument::pls_iterations << " " << endl;
	  cout << " " << setw(20) << left << "Efficient Solutions " << "|" << setw(20) << right << setprecision(0) << fixed << efficient_solutions.size() << " " << endl;
	  cout << " " << setw(20) << left << "Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(beginPLS,endPLS) + time_ms_Diff(beginPLS,endPLS)) << " " << endl;
	  cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
	}
      ToFile::saveParetoFrontier(efficient_solutions, *data);

      gettimeofday(&end,NULL);
      cout << endl;
      cout << "+" << setfill('-') << setw(15) << "+" << " SYNTHESIS " << "+" << setw(15) << "+" << endl;
      cout << setfill (' ');
      cout << " " << setw(20) << left << "Instance " << "|" << setw(20) << right << basename((char *)data->getFileName().c_str()) << " " << endl;
      cout << " " << setw(20) << left << "Efficient Solutions " << "|" << setw(20) << right << setprecision(0) << fixed << efficient_solutions.size() << " " << endl;
      cout << " " << setw(20) << left << "Total Time (ms) " << "|" << setw(20) << right << (1000*time_s_Diff(start,end) + time_ms_Diff(start,end)) << " " << endl;
      cout << "+" << setfill('-') << setw(42) << "+" << endl << endl;
      if(Argument::mode_export)
	{
	  //if(system("bash ./plot/plotNSGAPLS.sh"));
	  cout << "run gnuplot and put the following commands : " << endl;
	  cout << "gnuplot> load \"./plot/plotPLS.dat\"" << endl;
	  cout << "gnuplot> load \"./plot/plotNSGAEvolution.dat\"" << endl;
	  cout << "gnuplot> load \"./plot/plotEvolutionPLS.dat\"" << endl;
	}


    }
  if ( gnuplot_fp )
	{
		pclose(gnuplot_fp);
	}  
  vectorBox.clear();
  vectorBoxFinal.clear();
  delete data;
    
  return 0;
}
