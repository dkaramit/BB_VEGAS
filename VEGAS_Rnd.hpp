#ifndef VEGAS_Rand
#define VEGAS_Rand
#include"VEGAS.hpp"


//This defines a function that retunrs random numbers in the range [min,max].
// You can define your own here! 


template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,RandEn>::Random(LD min, LD max){
    std::uniform_real_distribution<LD> UnDist(min,max);
    return UnDist(RndE) ;
}

template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
int VEGAS<LD,NDim,NBin,NBinInit,RandEn>::RandomBin(){
    std::uniform_int_distribution<> UnInt(0, NBin-1);
    return UnInt(RndE);
}

// get random integer from 0 to NB
template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
int VEGAS<LD,NDim,NBin,NBinInit,RandEn>::RandomBin(int NB){
    std::uniform_int_distribution<> UnInt(0, NB-1);

    return UnInt(RndE);
}

#endif