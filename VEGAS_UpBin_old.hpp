#ifndef VEGAS_UpBin
#define VEGAS_UpBin
#include"VEGAS_Class.hpp"
#include"VEGAS_PartInts.hpp"


template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
void VEGAS<LD,NDim,NBin,NBinInit,RandEn>::UpdateBins(int NB){
    // This function basically normalizes the weights computed in PartialIntegrals

    //just call PartialIntegrals to give me the weights. 
    PartialIntegrals(NB);
    
    LD dx0;
    std::vector<LD> binsizes(NB);

    LD w0;//This is a temporary variable to keep weights[dim][0]. Do this in order to be able to reset
    // all weights at the end of each loop. 
    for(int dim = 0 ; dim < NDim ; ++dim){
        // this will give me the full integral needed to normalize the weights
        LD WeightNorm = 0;

        for(int bin = 0 ; bin < NB ; ++bin){
            binsizes[bin] = Grid[dim][bin+1] - Grid[dim][bin];
            WeightNorm += weights[dim][bin] * binsizes[bin];

        }
        
        // this is one way to find the  new delta x_0
        // delta x'_0 = delta x_0/(m_0+1)*\sum_{i=0}^{NBin}( delta x_i/(m_i+1) )^{-1}.
        // At the same time save the binsizes in order to update Grid directly
        dx0=0;
        
        // The first weight is important for all subsequesnt weights.
        //this is the normalized weight. 
        LD f0 = weights[dim][0] * binsizes[0] / WeightNorm;
        // this is the regulated weight.
        // w0 = 1 + std::pow( 1 + f0 * std::log(constK * f0 + 1) , alpha);
        w0=constK* std::pow((f0-1)/std::log(f0) ,alpha);
        for( int bin = 0 ; bin < NB ; ++bin){
            //this is the normalized weight. 
            LD f = weights[dim][bin] * binsizes[bin] / WeightNorm;
            // this is the regulated weight.
            // weights[dim][bin] = 1 + std::pow( 1 + f * std::log(constK * f + 1), alpha);
            weights[dim][bin] = constK* std::pow((f-1)/std::log(f) ,alpha);;
            dx0+=w0/binsizes[0]*(binsizes[bin]/weights[dim][bin]);
        }

        dx0=1/dx0;
        Grid[dim][0] = 0; // this is true by default. But put it to be sure...

        for( int bin = 0 ; bin < NB ; ++bin){
            Grid[dim][bin+1]=Grid[dim][bin]+dx0*binsizes[bin]/weights[dim][bin]*w0/binsizes[0];
            weights[dim][bin]=0; //You no longer need this weight. 
        }
        
    }
    // std::cout<<"\n";

}



#endif