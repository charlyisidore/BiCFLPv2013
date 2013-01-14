#
 #License and Copyright

 #Version : 1.1

 #This file is part of BiUFLv2012.

 #BiUFLv2012 is Copyright © 2012, University of Nantes

 #BiUFLv2012 is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

 #This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 #You should have received a copy of the GNU General Public License along with this program; if not, you can also find the GPL on the GNU web site.

 #In addition, we kindly ask you to acknowledge BiUFLv2012 and its authors in any program or publication in which you use BiUFLv2012. (You are not required to do so; it is up to your common sense to decide whether you want to comply with this request or not.) For general publications, we suggest referencing:  BiUFLv2012, MSc ORO, University of Nantes.

 #Non-free versions of BiUFLv2012 are available under terms different from those of the General Public License. (e.g. they do not require you to accompany any object code using BiUFLv2012 with the corresponding source code.) For these alternative terms you must purchase a license from Technology Transfer Office of the University of Nantes. Users interested in such a license should contact us (valorisation@univ-nantes.fr) for more information.
#

#!/bin/bash
rm -f ./plot/plotNSGAEvolution.dat ./plot/plotPLS.dat ./plot/plotEvolutionPLS.dat

INSTANCE=`ls ./res/*.out | sed -e "s/_.*//g" -e "s/.*\///g" | uniq`
echo "
instance = \""$INSTANCE"\"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set xlabel \"Obj. 1\"
set ylabel \"Obj. 2\"
set key font \",8\"

set title \""$INSTANCE" NSGA Evolution\" 
" >> ./plot/plotNSGAEvolution.dat
head -10 ./plot/plotNSGAEvolution.dat >> ./plot/plotPLS.dat
echo "set title \""$INSTANCE" PLS and NSGA\"" >> ./plot/plotPLS.dat

head -10 ./plot/plotNSGAEvolution.dat >> ./plot/plotEvolutionPLS.dat
echo "set title \""$INSTANCE" Evolution PLS \"" >> ./plot/plotEvolutionPLS.dat

echo "> Generating plot for this instance : " $INSTANCE

#echo "set output './plot/'.instance.'_PLS.png'" >> ./plot/plotPLS.dat
echo -ne "plot './res/"$INSTANCE"_ParetoFrontier.out' using 1:2 with points title \"pareto frontier\"">> ./plot/plotPLS.dat
#echo -ne ", './res/"$INSTANCE"_InitialPopulationNSGA.out' using 1:2 with points title \"initial nsga\"">> ./plot/plotPLS.dat
echo -ne ", './res/"$INSTANCE"_FinalPopulationNSGA.out' using 1:2 with points title \"final nsga\"">> ./plot/plotPLS.dat

#echo "set output './plot/'.instance.'_NSGAEvolution.png'" >> ./plot/plotNSGAEvolution.dat
echo -ne "plot './res/"$INSTANCE"_FinalPopulationNSGA.out' using 1:2 with points title \"final nsga\"">> ./plot/plotNSGAEvolution.dat
echo -ne ", './res/"$INSTANCE"_InitialPopulationNSGA.out' using 1:2 with points title \"initial nsga\"">> ./plot/plotNSGAEvolution.dat

#echo "set output './plot/'.instance.'_EvolutionPLS.png'" >> ./plot/plotEvolutionPLS.dat
echo -ne "plot './res/"$INSTANCE"_ParetoFrontier.out' using 1:2 with points title \"pareto frontier\"">> ./plot/plotEvolutionPLS.dat

j=1
for i in ./res/F*_PopulationNSGA_*; do 
    echo -ne ", '"$i"' using 1:2 with points title \""$j"\"" >> ./plot/plotNSGAEvolution.dat
    j=$((j+1))
done

j=1
for i in ./res/F*_PopulationPLS_*; do 
    echo -ne ", '"$i"' using 1:2 with points title \""$j"\"" >> ./plot/plotEvolutionPLS.dat
    j=$((j+1))
done

echo >> ./plot/plotNSGAEvolution.dat
echo >> ./plot/plotPLS.dat
echo >> ./plot/plotEvolutionPLS.dat
gnuplot  -persist ./plot/plotPLS.dat&
gnuplot -persist ./plot/plotNSGAEvolution.dat &
gnuplot -persist ./plot/plotEvolutionPLS.dat &
