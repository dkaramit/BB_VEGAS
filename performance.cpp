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
        for(int _=0 ; _<1e6;++_){Int.Random(0,1);}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"run: "<<i <<"  dt="<<dur.count()<<" s"  <<endl;
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
        cout<<"random. dt="<<dur.count()<<" s"  <<"\t\t\t";
        
        start = Time::now();
        for(int _=0 ; _<1e6;++_){RndE.seed(RndDiv () );}     
        finish = Time::now();
        dur = (finish - start);
        cout<<"seed. dt="<<dur.count()<<" s"  <<endl;
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
    timeRandom();



    return 0;
}
