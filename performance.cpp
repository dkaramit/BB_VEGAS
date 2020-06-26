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
int main(){
    LD res,sigma,R;
    
    auto start = Time::now();
    auto finish = Time::now();
    auto t0 = Time::now();
    auto t1 = Time::now();
    duration  dur;


    // declaration of integral should be slow
    t0 = Time::now();
    VEGAS<LD,Func,NDim,NBin,NBinInit>  Integral(f,NPoints , NBatches , NAdapts, AdaptPoints, 
                                                NAdaptSubDivs, SubDivPoints, constK , alpha);
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;



    t0 = Time::now();

    for (int i = 0; i < 50; i++){
        start = Time::now();
        R=Integral.Integrate( &res,&sigma );
        cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<"\t\t";
        finish = Time::now();
        dur = (finish - start);
        cout<< dur.count()  <<endl;
    }
    t1 = Time::now();
    dur = t1-t0;
    cout<< dur.count()  <<endl;


    return 0;
}
