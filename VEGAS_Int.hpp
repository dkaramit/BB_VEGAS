#ifndef VEGAS_Int
#define VEGAS_Int
#include"VEGAS.hpp"


template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,RandEn>::Integrate(LD *IntMean, LD *IntSigma   ){

    if(NBin!=NBinInit){SubDivision();}

    for (int n_adapt=0 ; n_adapt<NAdapts; ++n_adapt){UpdateBins();}

    return  IntegrateBatch(IntMean, IntSigma); 



}

#endif