#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"
//

// Dimention of integral
#define NDim 2

// initial number of bins (the same in every dimention)
#define NBinInit 1

// desired number of bins (run Subdivision until NBin is reached)
#define NBin 100


// number of points in each evaluation of the integral
#define NPoints 500
// number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 50

// Number of interations to use to refine the grid
#define NAdapts 10
// Number of points to use when refining the grid
#define AdaptPoints 100

// The constant that multiplies the regulated weights in the logarithm (you can take it to be ~1000).
// the function that regulates the weights is different that what peaple use.
//  K_const=0 implies no logarithmic term
#define constK 1e2

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.9

#ifndef LD
#define LD long double
#endif

// define the type of function to be used in VEGAS template
// 
typedef std::function<void(LD x[NDim], LD *retrn)> Func;


using std::cout;
using std::end;


int main(){
    #if 1
    VEGAS<LD,Func,NDim,NBin,NBinInit> 
    Integral([](LD x[NDim], LD *retrn){(*retrn)= 50*std::exp(-x[0]*x[0]*2)-1*x[1];},
        NPoints,NBatches,NAdapts, AdaptPoints ,constK,alpha);
    
    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    // Integral.PrintGrid();
    #endif
    return 0 ;
}