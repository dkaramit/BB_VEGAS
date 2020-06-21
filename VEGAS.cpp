#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"

// This show who to use VEGAS for  \int_1^\infty dx e^{-a x} \sqrt(x^2-1) = K_1(a)/a.
// To transform this to the interval [0,1], use x=1+\dfrac{u}{1-u}.



// Dimention of integral
#define NDim 1

// initial number of bins (the same in every dimention)
#define NBinInit 100

// desired number of bins (run subdivision until NBin is reached)
#define NBin 150

// number of points in each evaluation of the integral
#define NPoints 3000
// number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 50

// Number of interations to use to refine the grid
#define NAdapts 50
// Number of points to use when refining the grid
#define AdaptPoints 1000

// The constant that multiplies the regulated weights in the logarithm (you can take it to be ~1000).
// the function that regulates the weights is different that what peaple use.
//  K_const=0 implies no logarithmic term
#define constK 1e2

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.5

#ifndef LONG
#define LONG  
#endif

#define LD LONG double

// define the type of function to be used in VEGAS template
typedef std::function<void(LD u[NDim], LD *retrn)> Func;


using std::cout;
using std::end;


int main(){
    #if 1
    VEGAS<LD,Func,NDim,NBin,NBinInit> 
    Integral([](LD u[NDim], LD *retrn){ LD x=1+u[0]/(1-u[0]);  (*retrn)= std::exp(-1e-5*x)*std::sqrt(x*x-1)/(1-u[0])/(1-u[0]);},
        NPoints,NBatches,NAdapts, AdaptPoints ,constK,alpha);
    
    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    // Integral.PrintGrid();
    // Integral.PartialIntegrals();
    // Integral.PrintWeights();
    #endif
    return 0 ;
}