#ifndef VEGAS_Int
#define VEGAS_Int
#include"VEGAS_Class.hpp"
#include"VEGAS_SubDiv.hpp"
#include"VEGAS_UpBin.hpp"
#include"VEGAS_Int.hpp"
#include"VEGAS_IntTot.hpp"


template<class LD, int NDim, int NBin, int NBinInit, BatchEstimator Estimator, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,Estimator,RandEn>::Integrate(LD *IntMean, LD *IntSigma   ){

    if(NBin!=NBinInit){SubDivision();}

    for (int n_adapt=0 ; n_adapt<NAdapts; ++n_adapt){UpdateBins();}

    return  IntegrateBatch(IntMean, IntSigma); 

}

#endif