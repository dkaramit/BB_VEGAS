#ifndef VEGAS_PartInts
#define VEGAS_PartInts
#include"VEGAS_Class.hpp"
#include"VEGAS_Rnd.hpp"

// ---------------------------------------------------------------------------------------------------------
// ------------------------------------------- BIG PROBLEM -------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
//This is a big issue. There is no guarantee that all bins will be visited.
// So, there is a chance (especially for small AdaptPoints and big NBin) that a weight will be zero.
// This will make everything "nan".
//-------Solution-------:
// In UpdateBins, I regulate the weights so that they will never be zero. This is not a good solution because 
// It assigns the wrong weight if a bin is not visitied.
// The actual solution will be to make sure that every bin is visited.
// ---------------------------------------------------------------------------------------------------------


// // Calculate the  partial integrals as well as NPoints*\int_{0}^1 dx |f|.
// // The actual wheights are calculated in CalcWeights-Check.hpp, but here we just 
// // do this so that this will be calced for UpdateBins(), regulate pass the partial integrals
// // as m->m+1 , m-> (K* m log( m ))^alpha.

template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,RandEn>::PartialIntegrals(int NB){
    int Points=AdaptPoints;
    if(NB != NBin){ Points=SubDivPoints; }
    

    // Caution: PartialIntegrals assumes that weights = {0}. 
    // So, it *must* be run after the weights have been set to zero.
    // ----- Nevertheless, set weights to zero.
    for(int dim = 0 ; dim < NDim ; ++dim){
        for(int bin = 0 ; bin < NB ; ++bin){
            weights[dim][bin]=0;
        }
    }

    LD FuncPoint, point[NDim];
    int bins[NDim];

    //distribution of each dimension
    LD inv_p_dim[NDim];   // 1 / p_dim(x_dim) = NB * dx_dim
    LD dx_dim[NDim];

    LD full_inv_p;//the full distribution
    LD AbsIntegralEstimate = 0;//the integral value needed for the update

    // you get NPoints number of points
    for(int np=0 ; np < Points ;++np){
        
        full_inv_p = 1;



        // fill a point[NDims]. Get a random bin from each dimention. Here is where you can get 1/p(x).
        // Also in order to get the weight from this, you need to know in what bin is every point[dim].
        for(int dim = 0 ; dim < NDim ; ++dim){
            
            //This is a big issue. There is no guarantee that all bins will be visited.
            // So, there is a chance (especially for small AdaptPoints and big NBin) that a weight will be zero.
            // This will make everything "nan".
            bins[dim]=RandomBin(NB);


            dx_dim[dim] = Grid[dim][bins[dim]+1] - Grid[dim][bins[dim]];
            //note that I multiply by NB bacause this is the number of bins (NB=NBin only after the subdivision has ended)
            inv_p_dim[dim] = NB * dx_dim[dim];
            // accumilate the full distribution
            full_inv_p*= inv_p_dim[dim];

            point[dim] = Random( Grid[dim][bins[dim]] , Grid[dim][bins[dim]+1] ); 
        }
        
        Integrand( point , &FuncPoint );

        AbsIntegralEstimate += std::abs(FuncPoint) * full_inv_p/ Points;
        
        // This is the partial integral ( in the bin of dim, and [0,1] for all other dims). 
        // In each bin of each dim you just sum the contribution f^2/p.
        // You don't double-count anything because the dimensions are independent.
        for(int dim = 0 ; dim < NDim ; ++dim){
            weights[dim][bins[dim]]+=FuncPoint*FuncPoint * full_inv_p/inv_p_dim[dim]/dx_dim[dim]; // this is the updade in Lapage's paper
        }
        
    }
    
    //the update needs the square root of the the integral over f^2/p
    for (int dim = 0; dim < NDim; ++dim){
        for (int bin = 0; bin < NB; ++bin){
            weights[dim][bin] =std::sqrt(weights[dim][bin] / Points);

        }
    }

    return AbsIntegralEstimate ;
}


// ------------------------------------------------------------------- This visits all bins. Still causes "nan" for some reason.
// template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
// LD VEGAS<LD,NDim,NBin,NBinInit,RandEn>::PartialIntegrals(int NB)
// {
//     int Points = AdaptPoints;
//     if (NB != NBin) { Points = SubDivPoints; }

//     int SamplesPerBin = Points / NB;
//     if (SamplesPerBin < 1) { SamplesPerBin = 1; }

//     for (int dim = 0; dim < NDim; ++dim) {
//         for (int bin = 0; bin < NB; ++bin) {
//             weights[dim][bin] = 0;
//         }
//     }

//     LD FuncPoint;
//     LD point[NDim];
//     int bins[NDim];
//     LD dx_dim[NDim];
//     LD inv_p_dim[NDim];

//     LD AbsIntegralEstimate = 0;
//     int TotalSamples = 0;

//     for (int adapt_dim = 0; adapt_dim < NDim; ++adapt_dim){
//         for (int adapt_bin = 0; adapt_bin < NB; ++adapt_bin){
//             LD Accum = 0;

//             for (int sample = 0; sample < SamplesPerBin; ++sample){
//                 LD full_inv_p = 1;

//                 for (int dim = 0; dim < NDim; ++dim){
//                     if (dim == adapt_dim) {
//                         bins[dim] = adapt_bin;
//                     } else {
//                         bins[dim] = RandomBin(NB);
//                     }

//                     dx_dim[dim] = Grid[dim][bins[dim] + 1] - Grid[dim][bins[dim]];
//                     inv_p_dim[dim] = NB * dx_dim[dim];
//                     full_inv_p *= inv_p_dim[dim];
//                     point[dim] =Random(Grid[dim][bins[dim]],Grid[dim][bins[dim]+1]);
//                 }
//                 Integrand(point, &FuncPoint);
//                 LD inv_p_except = full_inv_p / inv_p_dim[adapt_dim];
                
//                 Accum +=FuncPoint * FuncPoint * inv_p_except
//                     / dx_dim[adapt_dim];

//                 AbsIntegralEstimate +=
//                     std::abs(FuncPoint) * full_inv_p;

//                 ++TotalSamples;
//             }

//             weights[adapt_dim][adapt_bin] =
//                 std::sqrt(Accum / SamplesPerBin);
//         }
//     }

//     return AbsIntegralEstimate / TotalSamples;
// }
#endif