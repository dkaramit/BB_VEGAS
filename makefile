Path=$(PWD)

CC=g++

# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

# optimization level
# OPT=O1
# OPT=O2
OPT=O3
# OPT=Ofast

FLG=  -std=c++17  -I "$(Path)" -lm -DLONG=$(LONG)  -$(OPT)

all: VEGAS.run


VEGAS.run: VEGAS.cpp VEGAS.hpp VEGAS_CalcWeights.hpp VEGAS_Int.hpp VEGAS_Rnd.hpp\
		   VEGAS_Aux.hpp VEGAS_Class.hpp VEGAS_IntTot.hpp VEGAS_SubDiv.hpp VEGAS_Batch.hpp\
		   VEGAS_Const.hpp VEGAS_PartInts.hpp VEGAS_UpBin.hpp

	$(CC) -o "$(Path)/VEGAS.run" "$(Path)/VEGAS.cpp" $(FLG) 


clean:
	@[ -f "$(Path)/VEGAS.run" ] && rm "$(Path)/VEGAS.run" || true