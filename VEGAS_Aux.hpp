#ifndef VEGAS_aux
#define VEGAS_aux
#include"VEGAS_Class.hpp"



// Define functions that help with getting some feedback for the Grid


template<class LD, int NDim, int NBin, BatchEstimator Estimator, class RandEn>
void VEGAS<LD,NDim,NBin,Estimator,RandEn>::PrintGrid(){
    for( int dim=0 ; dim<NDim ; ++dim ){
        for( auto _G: this->Grid[dim] ){
            std::cout<<_G<<" ";
        }
        std::cout<<"\n";
    }
}



template<class LD, int NDim, int NBin, BatchEstimator Estimator, class RandEn>
void VEGAS<LD,NDim,NBin,Estimator,RandEn>::PrintGrid(int dim){
    for( auto _G: this->Grid[dim] ){
            std::cout<<_G<<" ";
    }
    std::cout<<"\n";
}


template<class LD, int NDim, int NBin, BatchEstimator Estimator, class RandEn>
void VEGAS<LD,NDim,NBin,Estimator,RandEn>::PrintWeights(){
    for( int dim=0 ; dim<NDim ; ++dim ){
        for( auto _w: this->weights[dim] ){
            std::cout<<_w<<" ";
        }
        std::cout<<"\n";
    }
}




#endif