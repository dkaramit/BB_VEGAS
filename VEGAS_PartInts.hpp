#ifndef VEGAS_PartInts
#define VEGAS_PartInts
#include"VEGAS_Class.hpp"
#include"VEGAS_Rnd.hpp"



// Calculate the  partial integrals as well as NPoints*\int_{0}^1 dx |f|.
// The actual wheights are calculated in CalcWeights-Check.hpp, but here we just 
// do this so that this will be calced for UpdateBins(), regulate pass the partial integrals
// as m->m+1 , m-> (K* m log( m ))^alpha.

template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,RandEn>::PartialIntegrals(int NB){
    int Points=AdaptPoints;
    if(NB != NBin){ Points=SubDivPoints; }
    

    // Caution: PartialIntegrals assumes that weights = {0}. 
    // So, it *must* be run after the weights have been set to zero.
    // If you cannot guarantee this, uncomment for following.
    // ----- Set weights to zero.
    // for(int dim = 0 ; dim < NDim ; ++dim){
    //     for(int bin = 0 ; bin < NB ; ++bin){
    //         weights[dim][bin]=0;
    //     }
    // }

    LD FuncPoint, point[NDim];
    int bins[NDim];
    LD inv_dist;
    LD AbsInt=0;

    // you get NPoints number of points
    for(int np=0 ; np < Points ;++np){
        
        // The contribution of each point is |f(x)|/p(x), and 1/p(x)=Nbins*binsize (you extract this information when you get the point). 
        inv_dist=1;
        
        // fill a point[NDims]. Get a random bin from each dimention. Here is where you can get 1/p(x).
        // Also in order to get the weight from this, you need to know in what bin is every point[dim].
        for(int dim = 0 ; dim < NDim ; ++dim){
            bins[dim]=RandomBin(NB);

            point[dim] = Random( Grid[dim][bins[dim]] , Grid[dim][bins[dim]+1] ); 
            //note that I multiply by NB bacause this is the number of bins (NB=NBin only after the subdivision has ended)
            inv_dist*=NB*(Grid[dim][bins[dim]+1] - Grid[dim][bins[dim]]);
        }
        Integrand( point , &FuncPoint );
        AbsInt +=  std::abs(FuncPoint) * inv_dist;
        
        // This is the partial integral ( in the bin of dim, and [0,1] for all other dims). 
        // In each bin of each dim you just sum the contribution |f|/p.
        // You don't double-count anything because the dimensions are independent.
        for(int dim = 0 ; dim < NDim ; ++dim)
        {
            weights[dim][bins[dim]]+=std::abs(FuncPoint) * inv_dist;
        }
    }
    return AbsInt;
}


#endif