#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"


// Dimention of integral (the first two examples)
#define NDim 3

// initial number of bins (the same in every dimention)
#define NBinInit 5

// desired number of bins (run subdivision until NBin is reached)
#define NBin 25

// number of points in each evaluation of the integral
#define NPoints 1500
// number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 50

// Number of integrations to use to refine the grid
#define NAdapts 25
// Number of points to use when refining the grid
#define AdaptPoints 500

// Number of refinement during subdivision phase
#define NAdaptSubDivs 5
// Number of points to use during the subdivision phase 
#define SubDivPoints 500

// The constant that multiplies the regulated weights in the logarithm (you can take it to be ~1000).
// the function that regulates the weights is different that what peaple use.
//  K_const=0 implies no logarithmic term
#define constK 1e1

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.2


// For the random engine (last optional template argument og VEGAS) 
// you can use other engines provided by <random>, such as 
// std::minstd_rand
// std::mt19937 
// std::mt19937_64 
// std::ranlux48 

using std::cout;
using std::endl;



typedef std::function<void(double u[NDim], double *retrn)> Func;

void integrand(double u[NDim], double *retrn) {
    *retrn = u[0]+u[1]*u[2];
}


int main(){
    VEGAS<double,Func,NDim,NBin,NBinInit> Integral(integrand,
    NPoints , NBatches , NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints, constK , alpha);

    double result, err,R;

    R=Integral.Integrate(&result,&err);
    cout<<"I= "<<result<<" +/- "<<err<<" R= "<<R<<endl;


    return 0;
}