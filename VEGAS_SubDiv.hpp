#ifndef VEGAS_SubDiv
#define VEGAS_SubDiv
#include"VEGAS.hpp"

// Starting with NBinInit number of bin, this function subdivides the grid 
// until the number of bins reaches NBin.


VEGAS_Template
void VEGAS_Namespace::SubDivision(){
    // auto it=weights[0].begin();
    typename std::vector<LD>::iterator it;
    int ind;
    LD mid;

    for(int _ = NBinInit ; _<NBin ; _++){   
        // calculate the weights
        PartialIntegrals(_);
        
        // in each dimension, find the bin with the maximum weight, add a new point in the middle  
        //  of this bin. Then run UpdateBins to refine the new grid.
        for (int i = 0; i < NDim; i++){
            it=std::max_element(weights[i].begin() , weights[i].end());
            ind=std::distance(weights[i].begin() , it );
            mid=(Grid[i][ind]+Grid[i][ind+1])/2.;

            Grid[i].insert(Grid[i].begin()+ind+1,mid);
            weights[i].insert(it,0);
        }
        // UpdateBins(_+1);
        // adapt the new grid NAdaptSubDivs times
        for(int n_sub = 0; n_sub < NAdaptSubDivs ; ++n_sub){UpdateBins(_+1);}        
    }
}

#endif