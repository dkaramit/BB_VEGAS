#ifndef PARAMS
#define PARAMS

#include<iostream>
#include<functional>

// Dimensions of integrals
#define NDim 2

// Initial number of bins (the same in every dimension)
#define NBinInit 20

// Desired number of bins (run subdivision until NBin is reached)
#define NBin 100

// Number of points in each evaluation of the integral
#define NPoints 5000
// Number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 50

// Number of integrations to use to refine the grid
#define NAdapts 20
// Number of points to use when refining the grid
#define AdaptPoints 500

// Number of refinement during subdivision phase
#define NAdaptSubDivs 5
// Number of points to use during the subdivision phase 
#define SubDivPoints 500

// The constant that multiplies the regulated weights in the logarithm (you can take it to be ~1000).
// the function that regulates the weights is different that what peaple use.
//  K_const=0 implies no logarithmic term
#define constK 3e2

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.3

#ifndef LONG
#define LONG  
#endif

#define LD LONG double

// define the type of function to be used in VEGAS template
using Func=std::function<void(LD u[NDim], LD *retrn)>; //function pointer for 1D integrals

using std::cout;
using std::endl;



#endif