#ifndef VEGAS_const
#define VEGAS_const
#include"VEGAS.hpp"


template<class LD, int NDim, int NBin, BatchEstimator Estimator, class RandEn>
VEGAS<LD,NDim,NBin,Estimator,RandEn>::VEGAS( Func function, int NPoints, int NBatches, int NAdapts, int AdaptPoints, LD alpha){
    this->Integrand = function;
    this->NPoints = NPoints;
    this->NBatches = NBatches;
    this->NAdapts = NAdapts;
    this->AdaptPoints = AdaptPoints;
    this->alpha = alpha;

    for( int dim=0 ; dim<NDim ; ++dim ){
        Grid[dim].push_back(0);
        for( int bin=1 ; bin<NBin+1 ; ++bin ){
            Grid[dim].push_back(Grid[dim][bin-1] + (LD)1/(NBin));  
            weights[dim].push_back(0);
        }
        
    }


    // seed the random engine
    std::random_device RndDiv;
    RndE.seed(RndDiv());



}




#endif