#include<iostream>
#include<cmath>
#include<functional>
#include"VEGAS.hpp"
#include"params.hpp"


#include <chrono>

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


int main(){
    
    timeSubDiv();
    timeUpBin();
    timeIntTot();



    return 0;
}
