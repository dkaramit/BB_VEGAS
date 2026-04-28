#ifndef VEGAS_SubDiv
#define VEGAS_SubDiv
#include"VEGAS.hpp"

// Starting with NBinInit number of bin, this function subdivides the grid 
// until the number of bins reaches NBin.
template<class LD, int NDim, int NBin, int NBinInit, class RandEn>
void VEGAS<LD,NDim,NBin,NBinInit,RandEn>::SubDivision(){

    // we need an iterator to easily find the bin with the maximum weight
    typename std::vector<LD>::iterator it;
    int ind;
    LD mid;

    for(int number_of_bins = NBinInit ; number_of_bins<NBin ; number_of_bins++){   
        // calculate the weights
        PartialIntegrals(number_of_bins);
        
        // in each dimension, find the bin with the maximum weight, and add a new point in the middle  
        //  of this bin. Then run UpdateBins to refine the new grid.
        for (int dim = 0; dim < NDim; dim++){
            it=std::max_element(weights[dim].begin() , weights[dim].end());
            ind=std::distance(weights[dim].begin() , it );
            mid=(Grid[dim][ind]+Grid[dim][ind+1])/2.;

            Grid[dim].insert(Grid[dim].begin()+ind+1,mid);
            weights[dim].insert(it,0);
            
            // Set weights to zero. This is because subdivision ends here.
            // UpdateBins computes the weights for the new grid size,
            // So, it needs them to zero.
            for(int bin = 0 ; bin < number_of_bins+1 ; ++bin){ weights[dim][bin]=0;}
        }

        // refine the new grid NAdaptSubDivs times
        for(int n_sub = 0; n_sub < NAdaptSubDivs ; ++n_sub){UpdateBins(number_of_bins+1);}
    }
}

#endif