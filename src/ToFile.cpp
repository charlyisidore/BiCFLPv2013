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
 
#include "ToFile.hpp"

void ToFile::removeFiles()
{
  if(Argument::mode_export)
    {
      struct dirent *lecture;	
      DIR *repertoire;
      if( opendir("res") != 0 )
	{
	  repertoire = opendir("res");
	  while((lecture = readdir(repertoire)))
	    {
	      if(lecture->d_name[0] != '.')
		{	
		  string plot;
		  plot += "res/";
		  plot += lecture->d_name;
		  if( remove(plot.c_str()) == 0 )
		    {
		    }
		}
	    }
	}
    }
}


void ToFile::saveCorrelation(Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_Correlation.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
		
      if(oFile)
	{
	  for(unsigned int i = 0; i < data.getnbCustomer(); i++)
	    {
	      for(unsigned int j = 0; j < data.getnbFacility(); j++)
		{
		  oFile << data.getAllocationObj1Cost(i,j) 
			<< " " 
			<< data.getAllocationObj2Cost(i,j) 
			<< endl;
		}
	    }
		    
	}
      else
	{
	  cerr << "Unable to open the file !" << endl;
	}
		
      //Close the file
      oFile.close();
    }
}

void ToFile::saveInitialBoxes(vector<Box*> &vectorBox, Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_InitialBoxes.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
		
      if(oFile)
	{
	  for(unsigned int it = 0; it < vectorBox.size(); it++)
	    {
	      oFile << vectorBox[it]->getMinZ1() 
		    << "\t" 
		    << vectorBox[it]->getMinZ2() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ1() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ2() 
		    << endl;
	    }
	}
      else
	{
	  cerr << "Unable to open the file !" << endl;
	}
		
      //Close the file
      oFile.close();
    }
}

void ToFile::saveFilteringBoxes(vector<Box*> &vectorBox, Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_FilteringBoxes.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
		
      if(oFile)
	{
	  for(unsigned int it = 0; it < vectorBox.size(); it++)
	    {
	      oFile << vectorBox[it]->getMinZ1() 
		    << "\t" 
		    << vectorBox[it]->getMinZ2() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ1() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ2() 
		    << endl;
	    }
	}
      else
	{
	  cerr << "Unable to open the file !" << endl;
	}
		
      //Close the file
      oFile.close();
    }
}

void ToFile::saveReconstructionBoxes(vector<Box*> &vectorBox, Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_ReconstructionBoxes.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
		
      if(oFile)
	{
	  for(unsigned int it = 0; it < vectorBox.size(); it++)
	    {
	      oFile << vectorBox[it]->getMinZ1() 
		    << "\t" 
		    << vectorBox[it]->getMinZ2() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ1() 
		    << "\t" 
		    << vectorBox[it]->getMaxZ2() 
		    << endl;
	    }
	}
      else
	{
	  cerr << "Unable to open the file !" << endl;
	}
		
      //Close the file
      oFile.close();
    }
}

void ToFile::saveYN(list<Solution> &lsol, Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_YN.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
		
      list<Solution>::iterator iter;
		
      if(oFile)
	{
	  for(iter = lsol.begin(); iter != lsol.end(); iter++)
	    {
	      oFile << fixed 
		    << setprecision(0) 
		    << (*iter).getObj1() 
		    << "\t" 
		    << (*iter).getObj2() 
		    << "\t" 
		    << (*iter).getY_j()
		    << endl;
	    }
	}
      else
	{
	  cerr << "Unable to open the file !" << endl;
	}
		
      //Close the file
      oFile.close();
    }
}


void ToFile::saveParetoFrontier(EfficientSolution & efficient_population, Data &data)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_ParetoFrontier.out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
      if(oFile)
	{
	  for (unsigned int i=0; i<efficient_population.size(); ++i)
	    {
	      oFile << efficient_population[i] << std::endl;
	    }
	}
      //Close the file
      oFile.close();

    }
}

void ToFile::savePopulation(vector<Solution* > population, Data &data, string ext)
{
  if(Argument::mode_export)
    {
      //Opening output file
      string temp("res/");
      temp += basename((char *)data.getFileName().c_str());
      temp += "_";
      temp += ext;
      temp += ".out";
      ofstream oFile(temp.c_str(), ios::out | ios::trunc);
      if(oFile)
	{
	  for (unsigned int i=0; i<population.size(); ++i)
	    {
	      oFile << population[i] << std::endl;
	    }
	}
      //Close the file
      oFile.close();

    }
}


void ToFile::gnuplot_interactive(vector<Solution *> population)
{
	if (gnuplot_fp != 0){
		double minZ[2] = {population[0]->getObj1(), population[0]->getObj2()};
		double maxZ[2] = {population[0]->getObj1(), population[0]->getObj2()};
		for(unsigned int i = 1; i < population.size(); i++){
			minZ[0] = min(population[i]->getObj1(), minZ[0]);
			minZ[1] = min(population[i]->getObj2(), minZ[1]);
			maxZ[0] = max(population[i]->getObj1(), maxZ[0]);
			maxZ[1] = max(population[i]->getObj2(), maxZ[1]);
		}
		if(gnuplotPLS){
			maxX = 0;		
		}
		if(maxX == 0){
			minX = minZ[0]; minY = minZ[1];
			maxX = maxZ[0]; maxY = maxZ[1];
		}
		fputs("set nokey\n", gnuplot_fp);
		//fputs("set   autoscale\n",gnuplot_fp);
		fputs("unset log\n", gnuplot_fp);
		fputs("unset label\n", gnuplot_fp);
		//fputs("set xtic auto\n", gnuplot_fp);
		//fputs("set ytic auto\n", gnuplot_fp);
		//fprintf( gnuplot_fp, "set xrange [%f:%f]\n", minZ[0], maxZ[0] );
		//fprintf( gnuplot_fp, "set yrange [%f:%f]\n", minZ[1], maxZ[1] );
		fprintf( gnuplot_fp, "set xrange [%.2f:%.2f]\n", minX - (minX/1.2), maxX + (maxX/10000));
		fprintf( gnuplot_fp, "set yrange [%.2f:%.2f]\n", minY - (minY/1.2), maxY + (maxY/10000));
		fputs("set xlabel \"Obj. 1\"\n",gnuplot_fp);
		fputs("set ylabel \"Obj. 2\"\n",gnuplot_fp);
		fputs( "plot '-' title '1' linecolor rgb 'green'\n", gnuplot_fp );
		for(unsigned int i = 0; i < population.size(); i++){
			fprintf(gnuplot_fp, "%lf %lf\n", population[i]->getObj1(), population[i]->getObj2());
		}
		fputs( "e\n", gnuplot_fp );
	}
		
}
