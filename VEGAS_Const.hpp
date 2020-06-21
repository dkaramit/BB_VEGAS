#ifndef VEGAS_const
#define VEGAS_const
#include"VEGAS.hpp"


VEGAS_Template
VEGAS_Namespace::VEGAS( Func function, int NPoints, int NBatches, 
        int NAdapts, int AdaptPoints, int constK, LD alpha){
    this->Integrand = function;
    this->NPoints = NPoints;
    this->NBatches = NBatches;
    this->NAdapts = NAdapts;
    this->AdaptPoints = AdaptPoints;


    this->constK = constK;
    this->alpha = alpha;

    for( int dim=0 ; dim<NDim ; ++dim ){
        Grid[dim].push_back(0);
        for( int bin=1 ; bin<NBinInit+1 ; ++bin ){
            Grid[dim].push_back(Grid[dim][bin-1] + (LD)1/(NBinInit));  
            weights[dim].push_back(0);
        }
        
    }


    // This is the distribution that gets random bin
    std::uniform_int_distribution<> _UnInt(0, NBin-1);
    this-> UnInt =_UnInt;




}




#endif