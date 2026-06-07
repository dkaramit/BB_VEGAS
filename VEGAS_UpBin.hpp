#ifndef VEGAS_UpBin
#define VEGAS_UpBin
#include"VEGAS_Class.hpp"
#include"VEGAS_PartInts.hpp"


#include<limits>
template<class LD>
constexpr LD eps = std::sqrt(std::numeric_limits<LD>::epsilon());


template<class LD, int NDim, int NBin, BatchEstimator Estimator, class RandEn>
void VEGAS<LD,NDim,NBin,Estimator,RandEn>::UpdateBins(){
    // This function basically normalizes the weights computed in PartialIntegrals

    //just call PartialIntegrals to give me the weights. 
    PartialIntegrals();
    
    LD dx0;
    std::vector<LD> binsizes(NBin);
    std::vector<LD> smooth_weights(NBin);

    for(int dim = 0 ; dim < NDim ; ++dim){
        for(int bin = 0 ; bin < NBin ; ++bin){
            // compute smoothed weights. This prevents from weights updating uncontrollably and causing 
            // instabilities, nan, etc.
            LD left  = weights[dim][bin == 0    ? bin : bin - 1];
            LD mid   = weights[dim][bin];
            LD right = weights[dim][bin == NBin-1 ? bin : bin + 1];
            // this is one way to smooth the weights. 
            smooth_weights[bin] = (left + 2*mid + right) / 4;
        }
        // substitute teh weights with the smoothed ones
        for (int bin = 0; bin < NBin; ++bin) {weights[dim][bin] = std::max(smooth_weights[bin],eps<LD>*eps<LD>);}

    }


    // all weights at the end of each loop. 
    for(int dim = 0 ; dim < NDim ; ++dim){
        // this will give me the full integral needed to normalize the weights
        LD WeightNorm = 0;
        
        for(int bin = 0 ; bin < NBin ; ++bin){
            binsizes[bin] = Grid[dim][bin+1] - Grid[dim][bin];
            WeightNorm += weights[dim][bin] * binsizes[bin];    

        }
        

        dx0=0;
        // std::cout<<dim<<": \n";
        for( int bin = 0 ; bin < NBin ; ++bin){

            //compute the normalized weight. 
            LD f = weights[dim][bin] * binsizes[bin] / WeightNorm;
            LD delta = f - 1;
            if(std::abs(delta) < eps<LD>){weights[dim][bin]=1.+delta/2;}
            else{weights[dim][bin] = delta/std::log(f);}
            weights[dim][bin] = std::pow(weights[dim][bin],alpha);

            // std::cout<<weights[dim][bin] <<"\t" <<binsizes[bin] <<"\t"<< WeightNorm<<"\t"<<f<<"\n";
            dx0+=(binsizes[bin]/weights[dim][bin]);
            // without regularization do this:
            // dx0+=binsizes[bin]/weights[dim][bin];
        }

        dx0=1/dx0;
        Grid[dim][0] = 0; // this is true by default. But put it to be sure...

        for( int bin = 0 ; bin < NBin ; ++bin){

            Grid[dim][bin+1]=Grid[dim][bin]+dx0*binsizes[bin]/weights[dim][bin];

            // std::cout<<Grid[dim][bin] <<"\t" <<Grid[dim][bin+1]<<"\n";

            weights[dim][bin]=0; //You no longer need this weight. 
        }

    }

}



#endif