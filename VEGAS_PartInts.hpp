#ifndef VEGAS_PartInts
#define VEGAS_PartInts
#include"VEGAS_Class.hpp"
#include"VEGAS_Rnd.hpp"

// ---------------------------------------------------------------------------------------------------------
// ------------------------------------ a problem and its solution -----------------------------------------
// ---------------------------------------------------------------------------------------------------------
// if you randomly choose one bin at each dim, there is a chance that a bin will not be visited. 
// This makes the corresponding weight=0, which messes things up.
// ---------------------------------------------------------------------------------------------------------
//-------------------------------------------------Solution-------------------------------------------------:
// ---------------------------------------------------------------------------------------------------------
// build a list with all bins and shuffle it. Inside the "dim" loop, go in the bins using an increasing index.
// Once you reach the end of the bin list shuffle it again. This keeps the statistics fairly mixed while making sure
// that each bin is vesited (approximately) the same amount of times.
// ---------------------------------------------------------------------------------------------------------


// // Calculate the  partial integrals as well as NPoints*\int_{0}^1 dx |f|.
// // The actual wheights are calculated in CalcWeights-Check.hpp, but here we just 
// // do this so that this will be calced for UpdateBins(), regulate pass the partial integrals
// // as m->m+1 , m-> (K* m log( m ))^alpha.

template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
void VEGAS<LD,NDim,NBin,NBinInit,RandEn>::PartialIntegrals(int NB){
    int Points=AdaptPoints;
    
    
    
    if(NB != NBin){ Points=SubDivPoints; }
    
    
    // this will make sure that each bin will visited at least one time.
    if(Points < NB){ Points = NB; }
    //list with bins for all dims
    std::vector<std::vector<int>> bin_list(NDim, std::vector<int>(NB));
    std::vector<int> bin_list_index(NDim, 0);
    
    //keep track of the bin_visits to have more accurate statistics
    int bin_visits[NDim][NBin];
    
    // Caution: PartialIntegrals assumes that weights = {0}. 
    // So, it *must* be run after the weights have been set to zero.
    // ----- Nevertheless, set weights to zero.
    for(int dim = 0 ; dim < NDim ; ++dim){
        for(int bin = 0 ; bin < NB ; ++bin){
            weights[dim][bin]=0;
            bin_list[dim][bin]=bin;
            bin_visits[dim][bin] = 0;
        }
        std::shuffle(bin_list[dim].begin(), bin_list[dim].end(), RndE);
    }




    LD FuncPoint, point[NDim];
    int bins[NDim];

    //distribution of each dimension
    LD inv_p_dim[NDim];   // 1 / p_dim(x_dim) = NB * dx_dim
    LD dx_dim[NDim];

    LD full_inv_p;//the full distribution

    // you get NPoints number of points
    for(int np=0 ; np < Points ;++np){
        
        full_inv_p = 1;



        // fill a point[NDims]. Get a random bin from each dimention. Here is where you can get 1/p(x).
        // Also in order to get the weight from this, you need to know in what bin is every point[dim].
        for(int dim = 0 ; dim < NDim ; ++dim){
            
            // Naive way of choosing bins.
            // This causes a big issue. There is no guarantee that all bins will be visited.
            // So, there is a chance (especially for small AdaptPoints and big NBin) that a weight will be zero.
            // This will make everything "nan".
            // bins[dim]=RandomBin(NB);

            // instead choose a bin like this
            if(bin_list_index[dim] == NB){
                std::shuffle(bin_list[dim].begin(), bin_list[dim].end(), RndE);
                bin_list_index[dim] = 0;
            }
            bins[dim] = bin_list[dim][bin_list_index[dim]];
            bin_list_index[dim]++;


            dx_dim[dim] = Grid[dim][bins[dim]+1] - Grid[dim][bins[dim]];
            //note that I multiply by NB bacause this is the number of bins (NB=NBin only after the subdivision has ended)
            inv_p_dim[dim] = NB * dx_dim[dim];
            // accumilate the full distribution
            full_inv_p*= inv_p_dim[dim];

            point[dim] = Random( Grid[dim][bins[dim]] , Grid[dim][bins[dim]+1] ); 
        }
        
        Integrand( point , &FuncPoint );

        
        // This is the partial integral ( in the bin of dim, and [0,1] for all other dims). 
        // In each bin of each dim you just sum the contribution f^2/p.
        // Here p is the density of all dimensions without current  "dim", this is why I divide with inv_p_dim[dim]. 
        // You don't double-count anything because the dimensions are independent.
        for(int dim = 0 ; dim < NDim ; ++dim){
            weights[dim][bins[dim]]+=FuncPoint*FuncPoint * full_inv_p/inv_p_dim[dim]/dx_dim[dim]; // this is the updade in Lapage's paper
            ++bin_visits[dim][bins[dim]];
        }
        
    }
    
    //the update needs the square root of the the integral over f^2/p (here p is the density of all dimensions without current  "dim")
    for (int dim = 0; dim < NDim; ++dim){
        for (int bin = 0; bin < NB; ++bin){
            weights[dim][bin] =std::sqrt(weights[dim][bin] / bin_visits[dim][bin]);

        }
    }

    return ;
}


#endif