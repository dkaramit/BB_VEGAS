#ifndef VEGAS_class
#define VEGAS_class

// Just a thought: use different number of points for the wheights, and different for the integral.
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
// define some macros to avoid copy-paste of the same thing again and again:
// Func is a function type
// NDim the number of dimensions
// NBin the number of bins
// NBinInit the number of intial bins (if NBinInit ~= NBin, run subdivision until the number of buns is NBin)
#define VEGAS_Template template<class LD, class Func, int NDim, int NBin, int NBinInit>
#define VEGAS_Namespace VEGAS<LD,Func,NDim,NBin,NBinInit>



//Pass Dimention and number of bins in template, to make the code clearer (I think its faster than using new).   
VEGAS_Template
class VEGAS{
    public:
        Func Integrand; //this is the function to be integrated
        
        int NPoints, NBatches, NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints;
        // alpha is the exponent used to regulate the weights.
        // constK makes the difference between the large and small weights grater (provided is a large number).
        // See UpdateBins to see how it affects the regulated weights.
        LD  constK, alpha ; 

        // Notice that N number of bins need N+1 points to be defined
        // LD Grid[NDim][NBin+1];
        // LD weights[NDim][NBin];

        // allow for the bins to be dynamically allocated (Grid and weights are arrays of vectors)
        typename std::vector<LD> Grid[NDim],weights[NDim];

        std::random_device RndDiv;
        std::default_random_engine RndE;
        std::uniform_real_distribution<LD> UnDist;
        std::uniform_int_distribution<> UnInt;
        std::uniform_int_distribution<> UnIntN;


        VEGAS( Func function, int NPoints, int NBatches, 
        int NAdapts, int AdaptPoints, int NAdaptSubDivs, int SubDivPoints, int constK=50, LD alpha=0.9);
        
        ~VEGAS(){};

        //get a random point in [min,max]
        LD Random(LD min , LD max);
        // get random bin in NDimention NDim
        int RandomBin();
        int RandomBin(int NB);



        // Claculate the partial integrals. Returns \int|f|*NPoints. This is what we need to 
        // get the regulated weights. 
        LD PartialIntegrals(int NB=NBin);

        // subdivide the bin with the largest contribution untion you have NBin number of bins
        void SubDivision();

        // Update the bins
        void UpdateBins(int NB=NBin);

        // take the integral in [0,1]
        LD IntegrateTot();
        void IntegrateTot(LD *IntMean, LD *IntVariance);

        // Use this to take batches. IntMean is the result, IntSigma is sqrt(Var).
        // It returns chi^2/(NBathes-1) which should be close to 1.
        LD IntegrateBatch(LD *IntMean, LD *IntSigma);

        // Combine everything together. First adapt, and then run IntegrateBatch
        LD Integrate(LD *IntMean, LD *IntSigma);



        //---These are for the auxiliary functions. You can remove them with no effect.
        
        // prints binpoints of NDim
        void PrintGrid(int dim);
        // prints all binpoints
        void PrintGrid();
        
        // 
        void PrintDist();

        void PrintWeights();
        
        // Calculate the  weights. Just to check that the algorithm works. In practice we only need the partial integrals.
        LD CalculateWeights(int NB=NBin);
        // check that the sum of wieghts in each dimension is 1; (this is in CalcWeights-Check.hpp)
        void CheckWeights(int NB=NBin);
};

#endif