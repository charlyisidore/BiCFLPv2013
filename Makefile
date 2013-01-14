#===========================MakeFile==============================
# To compile 
#================================================================

EXDIR = $(shell pwd)

# ---------------------------------------------------------------------
# Compiler selection
# ---------------------------------------------------------------------

CPP = g++

# ---------------------------------------------------------------------
# Compiler options
# ---------------------------------------------------------------------

CPPOPT = -O2 -fPIC -fexceptions -DNDEBUG -DIL_STD -pthread

#------------------------------------------------------------
#
# Build and Execute directory
#
#------------------------------------------------------------

BIN_PATH = $(EXDIR)/bin
SRC_PATH = $(EXDIR)/src
OBJ_PATH = ${EXDIR}/obj
RES_PATH = ${EXDIR}/res
PLO_PATH = ${EXDIR}/plot

SOURCES = ${wildcard ${SRC_PATH}/*.cpp}
OBJECTS = ${patsubst ${SRC_PATH}/%.cpp, ${OBJ_PATH}/%.o, ${SOURCES}}

#------------------------------------------------------------
#
# make all : to compile all.
# make clean : delete the results files
# make clear : delete obj files, results files, binary file
#
#------------------------------------------------------------

CPP_EX = BiCFLPv2012

all: clear ${RES_PATH} ${OBJ_PATH} ${BIN_PATH} $(CPP_EX)

${RES_PATH}:
	@ mkdir -p $@

${OBJ_PATH}:
	@ mkdir -p $@

${BIN_PATH}:
	@ mkdir -p $@

$(CPP_EX): ${OBJECTS}
	@ echo ">> Creating executable"
	@ $(CPP) -Wall $(CPPOPT) $^ -o $(BIN_PATH)/$(CPP_EX)

${OBJ_PATH}/%.o : ${SRC_PATH}/%.cpp
	@ $(CPP) $(CPPOPT) -Wall -c $< -o $@

clear :
	@ echo ">> Clear results and plots"
	@ rm -f ${RES_PATH}/*.out
	@ /bin/rm -f ${PLO_PATH}/*.eps	
	@ /bin/rm -f ${PLO_PATH}/*.png
	@ rm -f ./plot/plotPLS.dat
	@ rm -f ./plot/plotNSGAEvolution.dat	
	@ chmod +rw ./plot/*.sh

clean : clear
	@ echo ">> Clean files and folders"
	@ /bin/rm -rf *.o *~ $(OBJ_PATH)/*.o
	@ /bin/rm -f ${PLO_PATH}/*~
	@ /bin/rm -f ${BIN_PATH}/*~
	@ /bin/rm -f ${OBJ_PATH}/*~
	@ /bin/rm -f ${RES_PATH}/*~
	@ /bin/rm -rf ${SRC_PATH}/*~
	@ /bin/rm -rf $(BIN_PATH)/$(CPP_EX)

#======================== END OF MakeFile =========================
