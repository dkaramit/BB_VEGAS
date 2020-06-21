#ifndef VEGAS_aux
#define VEGAS_aux
#include"VEGAS.hpp"



// Define functions that help with getting some feedback for the Grid


VEGAS_Template
void VEGAS_Namespace::PrintGrid(){
    for( int dim=0 ; dim<NDim ; ++dim ){
        for( auto _G: this->Grid[dim] ){
            std::cout<<_G<<" ";
        }
        std::cout<<"\n";
    }
}




VEGAS_Template
void VEGAS_Namespace::PrintGrid(int dim){
    for( auto _G: this->Grid[dim] ){
            std::cout<<_G<<" ";
    }
    std::cout<<"\n";
}


VEGAS_Template
void VEGAS_Namespace::PrintWeights(){
    for( int dim=0 ; dim<NDim ; ++dim ){
        for( auto _w: this->weights[dim] ){
            std::cout<<_w<<" ";
        }
        std::cout<<"\n";
    }
}




#endif