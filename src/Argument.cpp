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

#include "Argument.hpp"
#include <getopt.h>
#include <sstream>
#include <cstdlib>
#include <ctime>

int Argument::filtering( 0 );
int Argument::reconstruction( 0 );
int Argument::capacitated( 0 );
int Argument::mode_export( 0 );
int Argument::verbose( 0 );
int Argument::help( 0 );
int Argument::two_opt( 0 );
int Argument::pls( 0 );
unsigned int Argument::pls_poll_points( 10 );

unsigned int Argument::generations( 100 );
unsigned int Argument::nb_lambda( 10 );
unsigned int Argument::pls_iterations( 10 );

double Argument::Pc( 0.9 );
double Argument::Pm( 0.5 );

std::string Argument::filename;

// getopt long options array
static const struct option long_options[] = {
  { "filtering",       no_argument,       &Argument::filtering,      1                            },
  { "pls",             no_argument,       &Argument::pls,      1                            },
  { "reconstruction",  no_argument,       &Argument::reconstruction, 1                            },
  { "capacitated",     no_argument,       &Argument::capacitated,    1                            },
  { "generations",     required_argument, 0,                         Argument::id_generations },
  { "Pc",              required_argument, 0,                         Argument::id_Pc              },
  { "Pm",              required_argument, 0,                         Argument::id_Pm              },
  { "nb-lambda",       required_argument, 0,                         Argument::id_nb_lambda       },
  { "pls-poll",       required_argument, 0,                         Argument::id_pls_poll_points       },
  { "pls-iterations",       required_argument, 0,                         Argument::id_pls_iterations       },
    { "2opt",          no_argument,       &Argument::two_opt,         1                            },
  { "export",          no_argument,       &Argument::mode_export,         1                            },
  { "verbose",         no_argument,       &Argument::verbose,        1                            },
  { "quiet",           no_argument,       &Argument::verbose,        0                            },
  { "help",            no_argument,       &Argument::help,           1                            },
  { 0, 0, 0, 0 }
};

void Argument::parse( int argc, char *argv[] )
{
  int next_option;
  int option_index( 0 );

  const char * const short_options = "frvqpce:i";

  do
    {
      next_option = getopt_long( argc, argv, short_options, long_options, &option_index );
      switch ( next_option )
	{
	case 'f':
	  filtering = 1;
	  break;

	case 'e':
	  mode_export = 1;
	  break;

	case 'r':
	  reconstruction = 1;
	  break;

	case 'c':
	  capacitated = 1;
	  break;

	case 'v':
	  verbose = 1;
	  break;

	case 'h':
	  help = 1;
	  break;

	case 'q':
	    verbose = 0;
	  break;

	case 'p':
	  pls = 1;
	  break;

	case id_generations:
	  std::istringstream( optarg ) >> generations;
	  break;

	case id_Pc:
	  std::istringstream( optarg ) >> Pc;
	  break;

	case id_Pm:
	  std::istringstream( optarg ) >> Pm;
	  break;

	case id_nb_lambda:
	  std::istringstream( optarg ) >> nb_lambda;
	  break;

	case id_pls_iterations:
	  std::istringstream( optarg ) >> pls_iterations;
	  break; 

	case id_pls_poll_points:	
	  std::istringstream( optarg ) >> pls_poll_points;
	  break;

  
	case 0:
	case -1:
	  break;

	default:
	  abort();
	}
    }
  while ( next_option != -1 );

  if ( optind < argc )
    {
      filename = argv[optind];
    }
}
#define TRUE_FALSE_STRING(boolean_var) ((boolean_var == 1) ? ("true") : ("false"))

void Argument::print( std::ostream & os )
{
  os
    << "File: " << filename << std::endl
    << "Options:" << std::endl
    << "\tfiltering           = " << TRUE_FALSE_STRING(filtering)      << std::endl
    << "\treconstruction      = " << TRUE_FALSE_STRING(reconstruction) << std::endl
    << "\tcapacitated         = " << TRUE_FALSE_STRING(capacitated)    << std::endl;
  if(Argument::capacitated)
    {
      os << "\tpareto local search = " << TRUE_FALSE_STRING(pls) << std::endl
	 << "\tgenerations of nsga = " << generations << std::endl
	 << "\tPc                  = " << Pc          << std::endl
	 << "\tPm                  = " << Pm          << std::endl
	 << "\tnb-lambda           = " << nb_lambda   << std::endl
	 << "\tpls-poll            = " << pls_poll_points << ((pls == 0 ) ? " (not used)" : "") << std::endl
	 << "\tpls-iterations      = " << pls_iterations << ((pls == 0 ) ? " (not used)" : "") << std::endl
	 << "\t2opt                = " << TRUE_FALSE_STRING(two_opt) << ((pls == 0 ) ? " (not used)" : "") << std::endl
	 ;
    }
  os << "\texport              = " << TRUE_FALSE_STRING(mode_export) << std::endl
     << "\tverbose             = " << TRUE_FALSE_STRING(verbose)     << std::endl
     << std::endl;
}

void Argument::usage( const char * program_name, std::ostream & os )
{
  os
    << "Command is: " << program_name << " <instance> OPTIONS" << std::endl
    << "## OPTIONS ##" << std::endl
    << "-f   for filtering method"        << std::endl
    << "-r   for reconstruction method"   << std::endl
    << "-c   for capacitated problem"     << std::endl
    << "-p   to activate pareto local search"     << std::endl
    << "--generations      <nb_generations of nsga>                      (by default " << generations    << ")" << std::endl
    << "--Pc               <proba_crossover>                             (by default " << Pc             << ")" << std::endl
    << "--Pm               <proba_mutation>                              (by default " << Pm             << ")" << std::endl
    << "--nb-lambda        <range of lambda for the weighted sum>        (by default " << nb_lambda      << ")" << std::endl
    << "--pls-poll         <nb poll points of pls>                       (by default " << pls_iterations << ")" << std::endl
    << "--pls-iterations   <nb iterations of pls>                        (by default " << pls_iterations << ")" << std::endl
    << "--2opt      to activate 2opt local search                        (very expensive)" << std::endl
    << "--verbose   for verbose mode"   << std::endl
    << "--export    to export results"  << std::endl;
}

