#ifndef VEGAS_UpBin
#define VEGAS_UpBin
#include"VEGAS.hpp"


template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
void VEGAS<LD,NDim,NBin,NBinInit,RandEn>::UpdateBins(int NB){

    LD AbsInt = PartialIntegrals(NB);
    LD dx0;
    LD binsizes[NB];

    LD w0;//This is a temporary variable to keep weights[dim][0]. Do this in order to be able to reset
    // all weights at the end of each loop. 
    for(int dim = 0 ; dim < NDim ; ++dim)
        {
            // this is one way to find the  new delta x_0
            // delta x'_0 = delta x_0/(m_0+1)*\sum_{i=0}^{NBin}( delta x_i/(m_i+1) )^{-1}.
            // At the same time save the binsizes in order to update Grid directly
            dx0=0;
            

            // this is weights[dim][0] (the regulated one) for bin=m of this dim.
            w0=1+ std::pow(1+weights[dim][0]/AbsInt * std::log(constK*weights[dim][0]/AbsInt + 1 ),alpha  );

            for( int bin = 0 ; bin < NB ; ++bin)
            {
                binsizes[bin]=Grid[dim][bin+1]-Grid[dim][bin];

                weights[dim][bin]=1+ std::pow(1+weights[dim][bin]/AbsInt * std::log(constK*weights[dim][bin]/AbsInt + 1 ),alpha  );

                dx0+=w0/binsizes[0]*(binsizes[bin]/weights[dim][bin]);
            }
            dx0=1/dx0;

            Grid[dim][0]=0; // this is true by default. But put it to be sure...
            for( int bin = 0 ; bin < NB ; ++bin)
            {
                Grid[dim][bin+1]=Grid[dim][bin]+ dx0*binsizes[bin]/weights[dim][bin]*w0/binsizes[0];
                weights[dim][bin]=0; //You no longer need this weight. 
            }


        
        }


}



#endif