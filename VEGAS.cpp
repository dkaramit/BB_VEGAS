#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"


// This is an example on how to use VEGAS. It calculates the two 1D and one 10D integrals (see macros below).

// test 1 (basically a bessel function) K_1(10^{-5})/10^{-5} 
#define Bessel // result should around 10^10 

// integral over a Gaussian function with a sharp peak at x=0.5
#define Gauss // result should around 0.177

// integral over a product of Gaussians with sharp peaks around x_i=0.1*i, for i=1,2..10.
#define NDGauss // result should around 1.29 \times 10^{-8}



// Dimensions of integrals
#define NDim1 1
#define NDim2 10

// Initial number of bins (the same in every dimension)
#define NBinInit 20

// Desired number of bins (run subdivision until NBin is reached)
#define NBin 100

// Number of points in each evaluation of the integral
#define NPoints 1000
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
using Func1=std::function<void(LD u[NDim1], LD *retrn)>; //function pointer for 1D integrals
using Func2=std::function<void(LD u[NDim2], LD *retrn)>; //function pointer for 10D integrals

using std::cout;
using std::endl;


// you can do something like this. But seems pointless if you only have a few lines of code.
// using VEGAS1D = VEGAS<LD,Func1,NDim1,NBin,NBinInit>;
// using VEGAS10D = VEGAS<LD,Func2,NDim2,NBin,NBinInit>;


int main(){

    {
    #ifdef Bessel
    VEGAS<LD,Func1,NDim1,NBin,NBinInit> 
    Integral([](LD u[NDim1], LD *retrn){ LD x=1+u[0]/(1-u[0]);  (*retrn)= std::exp(-1e-5*x)*std::sqrt(x*x-1)/(1-u[0])/(1-u[0]);},
        NPoints , NBatches , NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints, constK , alpha);
    
    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    // Integral.PrintGrid();
    // Integral.PartialIntegrals();
    // Integral.PrintWeights();
    #endif
    }



    {
    #ifdef Gauss
    VEGAS<LD,Func1,NDim1,NBin,NBinInit> 
    Integral([](LD x[NDim1], LD *retrn){  (*retrn)= std::exp(-100.*std::pow(x[0]-0.5,2)) ;},
        NPoints , NBatches , NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints, constK , alpha);
    
    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    // Integral.PrintGrid();
    // Integral.PartialIntegrals();
    // Integral.PrintWeights();
    #endif
    }


    {
    #ifdef NDGauss
    VEGAS<LD,Func2,NDim2,NBin,NBinInit> 
    Integral([](LD x[NDim2], LD *retrn){  
        (*retrn)=1;
        for (int i=0 ; i<NDim2 ; ++i)
        {
           (*retrn)*= std::exp(-100.*std::pow(x[i]-0.1*(i+1),2)) ;
        }
        
        
        },
        NPoints , NBatches , NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints, constK , alpha);
    
    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    // Integral.PrintGrid();
    // Integral.PartialIntegrals();
    // Integral.PrintWeights();
    #endif
    }






    return 0 ;
}