#ifndef VEGAS_Rand
#define VEGAS_Rand
#include"VEGAS.hpp"


//This defines a function that retunrs random numbers in the range [min,max].
// You can define your own here! 


VEGAS_Template
LD VEGAS_Namespace::Random(LD min, LD max){
    std::uniform_real_distribution<LD> UnDist;
    return ( UnDist(RndE)*(max - min) + min ) ;
}

VEGAS_Template
int VEGAS_Namespace::RandomBin(){
    std::uniform_int_distribution<> UnInt(0, NBin-1);
    return UnInt(RndE);
}

// get random integer from 0 to NB
VEGAS_Template
int VEGAS_Namespace::RandomBin(int NB){
    std::uniform_int_distribution<> UnInt(0, NB-1);

    return UnInt(RndE);
}

#endif