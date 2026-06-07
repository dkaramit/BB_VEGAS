#include<iostream>
#include<cmath>
#include"VEGAS.hpp"


// Dimention of integral (the first two examples)
#define NDim 3

// initial number of bins (the same in every dimention)
#define NBinInit 50

// desired number of bins (run subdivision until NBin is reached)
#define NBin 50

// number of points in each evaluation of the integral
#define NPoints 500
// number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 25

// Number of integrations to use to refine the grid
#define NAdapts 100
// Number of points to use when refining the grid
#define AdaptPoints 5000

// Number of refinement during subdivision phase
#define NAdaptSubDivs 10
// Number of points to use during the subdivision phase 
#define SubDivPoints 500

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.04


// For the random engine (last optional template argument og VEGAS) 
// you can use other engines provided by <random>, such as 
// std::minstd_rand
// std::mt19937 
// std::mt19937_64 
// std::ranlux48 

using std::cout;
using std::endl;




void integrand(double u[NDim], double *retrn) {
    // *retrn = u[0]+u[1]+u[2];
    *retrn = 1e7*std::exp(-(std::pow(u[0]-0.5,2)*std::pow(u[1]-0.5,2)*std::pow(u[2]-0.5,2))*1e12);
    
    // *retrn =0; 
    // std::exp( - std::pow(u[0] -0.5,2 )/10 ) * std::exp( - std::pow(u[1] -0.5,2 )/10 ) * std::exp( - std::pow(u[2] -0.5,2 )/10 )*
    // std::sin(u[0] -0.5)*std::sin(u[1] -0.5)*std::sin(u[2] -0.5);
}


int main(){
    VEGAS<double,NDim,NBin,NBinInit,BatchEstimator::vegas> Integral(integrand,
    NPoints , NBatches , NAdapts, AdaptPoints, NAdaptSubDivs, SubDivPoints , alpha);

    // {
    //     double result, err;
    //     Integral.Integrate(&result,&err);
    //     cout<<"I= "<<result<<" +/- "<<err<<endl;
    // }
    double result, err,R;
    R=Integral.Integrate(&result,&err);
    cout<<"I= "<<result<<" +/- "<<err<<" R= "<<R<<endl;


    return 0;
}