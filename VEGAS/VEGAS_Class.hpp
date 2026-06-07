#ifndef VEGAS_class
#define VEGAS_class

#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
#include<random>
#include<functional>
#include<VEGAS_Estimators.hpp>


// define some macros to avoid copy-paste of the same thing again and again:
// NDim the number of dimensions
// NBin the number of bins
// RandEn the random engine. This is optional, since I use a std::mt19937_64 as default

//Pass Dimension and number of bins in template, to make the code clearer (I think its faster than using new).   
template<class LD, int NDim, int NBin, BatchEstimator Estimator = BatchEstimator::vegas , class RandEn=std::mt19937_64>
class VEGAS{
    using Func = std::function<void(LD u[NDim], LD *retrn)>;
    public:
        Func Integrand; //this is the function to be integrated
        
        int NPoints, NBatches, NAdapts, AdaptPoints;
        
        // alpha is the exponent used to regulate the weights.
        LD  alpha ; 

        // Notice that N number of bins need N+1 points to be defined
        // LD Grid[NDim][NBin+1];
        // LD weights[NDim][NBin];

        // allow for the bins to be dynamically allocated (Grid and weights are arrays of vectors)
        typename std::vector<LD> Grid[NDim],weights[NDim];

        RandEn RndE;


        VEGAS( Func function, int NPoints, int NBatches, int NAdapts, int AdaptPoints, LD alpha=0.9);
        
        ~VEGAS(){};

        //get a random point in [min,max]
        LD Random(LD min , LD max);
        // get random bin in NDimention NDim
        int RandomBin();
        int RandomBin(int NB);



        // Claculate the partial integrals. Returns \int|f|*NPoints. This is what we need to 
        // get the regulated weights. 
        void PartialIntegrals();

        // Update the bins
        void UpdateBins();

        // take the integral in [0,1]
        LD IntegrateTot();
        void IntegrateTot(LD *IntMean, LD *IntVariance);

        // Use this to take batches. IntMean is the result, IntSigma is sqrt(Var).
        // It returns chi^2/(NBathes-1) which should be close to 1.
        LD IntegrateBatch(LD *IntMean, LD *IntSigma);
        LD batch_estimator(LD *IntMean, LD *IntSigma, const std::vector<LD>& means , const std::vector<LD>& vars){
            if constexpr (Estimator == BatchEstimator::vegas){return vegas_estimator(IntMean,IntSigma,means,vars);}
            else if constexpr (Estimator == BatchEstimator::least_squares){return least_squares_estimator(IntMean,IntSigma,means,vars);}
            return plain_estimator(IntMean,IntSigma,means,vars);
        }

        // Combine everything together. First adapt, and then run IntegrateBatch
        LD Integrate(LD *IntMean, LD *IntSigma);
};

#endif