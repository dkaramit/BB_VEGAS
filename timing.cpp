#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"
#include <chrono>



// Dimention of integral
#define NDim 1

// initial number of bins (the same in every dimention)
#define NBinInit 25

// desired number of bins (run subdivision until NBin is reached)
#define NBin 100

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

#ifndef LONG
#define LONG  
#endif

#define LD LONG double

// define the type of function to be used in VEGAS template
typedef std::function<void(LD u[NDim], LD *retrn)> Func;


using std::cout;
using std::endl;























void f(LD x[NDim], LD *retrn){
        (*retrn) = std::exp( 3*x[0] )+ std::exp( -3*x[1] );
}


using Time = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double> ;



void timeSubDiv( ){
    cout<<"========================Timing SubDivision========================"<<endl;

    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;

    VEGAS<LD,Func,NDim,NBin,NBinInit>  Int(f,NPoints , NBatches , NAdapts, AdaptPoints, 
                                                NAdaptSubDivs, SubDivPoints, constK , alpha);


    t0 = Time::now();

    for (int i = 0; i < 10; i++){
        start = Time::now();
        Int.SubDivision();      
        finish = Time::now();
        dur = (finish - start);
        cout<<"run: "<<i <<"  dt="<<dur.count()<<" s"  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;


}


void timeUpBin( ){
    cout<<"========================Timing UpdateBins========================"<<endl;

    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;

    VEGAS<LD,Func,NDim,NBin,NBin>  Int(f,NPoints , NBatches , NAdapts, AdaptPoints, 
                                                NAdaptSubDivs, SubDivPoints, constK , alpha);


    t0 = Time::now();

    for (int i = 0; i < 10; i++){
        start = Time::now();
        for(int _=0 ; _<500;++_){Int.UpdateBins(); }     
        finish = Time::now();
        dur = (finish - start);
        cout<<"run: "<<i <<"  dt="<<dur.count()<<" s"  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;


}

void timeIntTot( ){
    cout<<"========================Timing IntegrateTot========================"<<endl;
    LD res,var;
    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;

    VEGAS<LD,Func,NDim,NBin,NBin>  Int(f,NPoints , NBatches , NAdapts, AdaptPoints, 
                                                NAdaptSubDivs, SubDivPoints, constK , alpha);


    t0 = Time::now();

    for (int i = 0; i < 10; i++){
        start = Time::now();
        for(int _=0 ; _<70;++_){Int.IntegrateTot(&res,&var);}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"run: "<<i <<"  dt="<<dur.count()<<" s"  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;
}


void timeRandomVEGAS( ){
    cout<<"========================Timing Random from VEGAS========================"<<endl;
    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;

    VEGAS<LD,Func,NDim,NBin,NBin>  Int(f,NPoints , NBatches , NAdapts, AdaptPoints, 
                                                NAdaptSubDivs, SubDivPoints, constK , alpha);


    t0 = Time::now();

    for (int i = 0; i < 10; i++){
        start = Time::now();
        for(int _=0 ; _<5;++_){cout<<Int.Random(0,1)<<" ";}     
        finish = Time::now();
        dur = (finish - start);
        cout<<endl<<"run: "<<i <<"  dt="<<dur.count()<<" s"  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;
}

void timeRandom( ){
    cout<<"========================Timing Random========================"<<endl;
    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;

    std::random_device RndDiv;
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    

    t0 = Time::now();

    for (int i = 0; i < 10; i++){
        start = Time::now();
        for(int _=0 ; _<1e6;++_){UnDist( RndE );}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"random. dt="<<dur.count()<<" s"  <<"\t";
        
        start = Time::now();
        for(int _=0 ; _<1e6;++_){RndE.seed(RndDiv () );}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"seed. dt="<<dur.count()<<" s"  <<"\t";

        start = Time::now();
        for(int _=0 ; _<1e6;++_){RndDiv() ;}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"divice. dt="<<dur.count()<<" s"  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;
}


int main(){
    
    // timeSubDiv();
    // timeUpBin();
    // timeIntTot();
    timeRandomVEGAS();
    // timeRandom();



    return 0;
}
