Path=$(PWD)

CC=g++

# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles (safer if you have a lot of bins, but slower)

# optimization level
# OPT=-O0
# OPT=-O1
# OPT=-O2
OPT=-O3
# OPT=-Ofast # faster, except when it fails :)


#run make DEBUG=1 for debugging
ifeq ($(DEBUG),1)
  OPT = -O0 -g 
endif

FLG=  -std=c++17  -I "$(Path)" -lm -DLONG=$(LONG)  $(OPT) -I VEGAS
HPP=$(wildcard VEGAS/*.hpp)


all: VEGAS.run SimpleExample.run Example.run FunctorExample.run

VEGAS.run: $(HPP) VEGAS.cpp makefile


	$(CC) -Wall -o "$(Path)/VEGAS.run" "$(Path)/VEGAS.cpp" $(FLG) 


Example.run: Example.cpp $(HPP) makefile


	$(CC) -Wall -o "$(Path)/Example.run" "$(Path)/Example.cpp" $(FLG) 

SimpleExample.run: SimpleExample.cpp $(HPP) makefile


	$(CC) -Wall -o "$(Path)/SimpleExample.run" "$(Path)/SimpleExample.cpp" $(FLG) 

FunctorExample.run: FunctorExample.cpp $(HPP) makefile


	$(CC) -Wall -o "$(Path)/FunctorExample.run" "$(Path)/FunctorExample.cpp" $(FLG) 


clean:
	rm -f *.run