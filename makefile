Path=$(PWD)

CC=g++

# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles (safer if you have a lot of bins, but slower)

# optimization level
# OPT=O1
# OPT=O2
OPT=O3
# OPT=Ofast # faster, except when it fails :)

FLG=  -std=c++17  -I "$(Path)" -lm -DLONG=$(LONG)  -$(OPT)

all: VEGAS.run SimpleExample.run Example.run


VEGAS.run: VEGAS.cpp VEGAS.hpp VEGAS_CalcWeights.hpp VEGAS_Int.hpp VEGAS_Rnd.hpp\
		   VEGAS_Aux.hpp VEGAS_Class.hpp VEGAS_IntTot.hpp VEGAS_SubDiv.hpp VEGAS_Batch.hpp\
		   VEGAS_Const.hpp VEGAS_PartInts.hpp VEGAS_UpBin.hpp makefile


	$(CC) -Wall -o "$(Path)/VEGAS.run" "$(Path)/VEGAS.cpp" $(FLG) 


Example.run: Example.cpp VEGAS.hpp VEGAS_CalcWeights.hpp VEGAS_Int.hpp VEGAS_Rnd.hpp\
		   VEGAS_Aux.hpp VEGAS_Class.hpp VEGAS_IntTot.hpp VEGAS_SubDiv.hpp VEGAS_Batch.hpp\
		   VEGAS_Const.hpp VEGAS_PartInts.hpp VEGAS_UpBin.hpp makefile


	$(CC) -Wall -o "$(Path)/Example.run" "$(Path)/Example.cpp" $(FLG) 

SimpleExample.run: SimpleExample.cpp VEGAS.hpp VEGAS_CalcWeights.hpp VEGAS_Int.hpp VEGAS_Rnd.hpp\
		   VEGAS_Aux.hpp VEGAS_Class.hpp VEGAS_IntTot.hpp VEGAS_SubDiv.hpp VEGAS_Batch.hpp\
		   VEGAS_Const.hpp VEGAS_PartInts.hpp VEGAS_UpBin.hpp makefile


	$(CC) -Wall -o "$(Path)/SimpleExample.run" "$(Path)/SimpleExample.cpp" $(FLG) 

FunctorExample.run: FunctorExample.cpp VEGAS.hpp VEGAS_CalcWeights.hpp VEGAS_Int.hpp VEGAS_Rnd.hpp\
		   VEGAS_Aux.hpp VEGAS_Class.hpp VEGAS_IntTot.hpp VEGAS_SubDiv.hpp VEGAS_Batch.hpp\
		   VEGAS_Const.hpp VEGAS_PartInts.hpp VEGAS_UpBin.hpp makefile


	$(CC) -Wall -o "$(Path)/FunctorExample.run" "$(Path)/FunctorExample.cpp" $(FLG) 


clean:
	rm -f *.run