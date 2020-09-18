/*Another example on how to use VEGAS*/


#include<iostream>
#include<iomanip>
#include<cmath>
#include<functional>
#include<chrono>
#include"VEGAS.hpp"


/*----------I find this a useful way to use long double easily--------------*/
#ifndef LONG
#define LONG  
#endif
#define LD LONG double
/*-----------------------------------------------*/

#define NDim 1


// this uses the life of a variable to basically measure time inside a scope! 
class Timer{
    public:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> finish;
    std::chrono::duration<double> dt;
    Timer(){
        start = std::chrono::high_resolution_clock::now();
    };
    ~Timer(){
        finish = std::chrono::high_resolution_clock::now();
        dt = finish - start;
        std::cout<<"dt="<<dt.count();
    };
};


// this is a very sharp function. So, we expect VEGAS to be able and minimize the variance 
// (with R closer to 1) compared to the plain MC case (no subdivision, and no adaptation).
// \int_{0}^{1} dx f(x) \approx 0.0056
void integrand(LD x[NDim], LD *retrn){
    *retrn = std::exp(-1e5*std::pow(x[0]-0.5,2)) ;
} 

// function pointer
using Func = std::function<void(LD x[NDim], LD *retrn)> ;
// the two settings we'll comare
using vegas = VEGAS<LD,Func,NDim,50,25>;
using plain = VEGAS<LD,Func,NDim,1,1>; // this is basically a plain Monte Carlo 

int main(){
    
   


    LD result, err,R;

    std::cout<<std::left<<"VEGAS";
      std::cout.fill('=');
    std::cout.width(95);
      std::cout.fill('=');
    std::cout<<std::right<<"Plain"<<std::endl; 

    for(int i=0 ; i<500; ++i){
        {
            Timer _;// the timer will print the duration at the end of this scope
            // Remeber that you can use "named" parameters (clearer what you pass). 
            vegas VIntegral{integrand,300,100,5,300,5,300,0.1,0.3};
            
            //you could do something like the following, but it doesn't work on mac... 
            // vegas VIntegral {.function = integrand,
            //                 .NPoints = 300, .NBatches = 100, 
            //                 .NAdapts = 5, .AdaptPoints = 300, 
            //                 .NAdaptSubDivs = 5, .SubDivPoints = 300, 
            //                 .constK = 0.1, .alpha = 0.3};


            R=VIntegral.Integrate(&result,&err);
            std::cout<<std::setprecision(8);
            std::cout.width(2);
            std::cout<<result<<"\t";
            std::cout.width(2);
            std::cout<<std::right<<"+/-"<<err/result*1e2<<"%"<<"\t";
            std::cout.width(2);
            std::cout<<std::right<<"R="<<R<<"\t";
        }
        std::cout<<"\t || \t"; 

        {
            Timer _;
            // since the number of bins are set to 1,  NAdapts, NAdaptSubDivs, etc. should not play ant role,
            // but it's clearer if we put them to 0.
            // This choice gives consistent results (still with higher error), but much slower.
            plain PIntegral {integrand, 2000,200, 0,0, 0, 0, 0., 0.};

            R=PIntegral.Integrate(&result,&err);
            std::cout<<std::setprecision(8);
            std::cout.width(2);
            std::cout<<result<<"\t";
            std::cout.width(2);
            std::cout<<std::right<<"+/-"<<err/result*1e2<<"%"<<"\t";
            std::cout.width(2);
            std::cout<<std::right<<"R="<<R<<"\t";
        }
        std::cout<<std::endl;
    }

    
    
    return 0;
}