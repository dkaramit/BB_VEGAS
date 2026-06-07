#ifndef Estimators_class
#define Estimators_class



enum class BatchEstimator {
    vegas,
    least_squares,
    plain,
};


template<class LD>
LD vegas_estimator(LD *IntMean, LD *IntSigma, const std::vector<LD>& means , const std::vector<LD>& vars){
    
    LD SumI3Var=0; //To get Sum_b I_b^3/\sigma_b^2
    LD SumI2Var=0; //To get Sum_b I_b^2/\sigma_b^2

    LD SumInvVar= 0; // To get Sum_b 1/\sigma_b^2 
    LD SumI1Var=0;  // To get Sum_b I_b/\sigma_b^2


    size_t batch_size=means.size();
    LD res,var,chi2; //temporary variables to get the results from IntegrateTot
    for(size_t batch=0 ; batch<batch_size ; ++batch){
        res = means[batch];
        // var = vars[batch];
        var = std::max(vars[batch],std::numeric_limits<LD>::min());
        
        
        SumI2Var+=res*res/var;
        
        SumI3Var+=res*res*res/var;
        
        SumInvVar+=static_cast<LD>(1.)/var;
        
        SumI1Var+=res/var;
    }

    SumI2Var = std::max(SumI2Var,std::numeric_limits<LD>::min());

    *IntMean=SumI3Var/SumI2Var;
    
    *IntSigma=std::abs(*IntMean)/std::sqrt( SumI2Var);

    chi2=SumI2Var+(*IntMean)*(*IntMean)*SumInvVar-2*SumI1Var*(*IntMean) ;

    return  chi2/(batch_size-1);
}


template<class LD>
LD least_squares_estimator(LD *IntMean, LD *IntSigma, const std::vector<LD>& means , const std::vector<LD>& vars){
    
    LD SumIVar=0; //To get Sum_b I_b/\sigma_b^2
    
    LD SumInvVar=0;  // To get Sum_b 1/\sigma_b^2
    
    LD SumI2Var=0; //To get Sum_b I_b^2/\sigma_b^2,  for \chi^2

    size_t batch_size=means.size();
    LD res,var,chi2; //temporary variables to get the results from IntegrateTot
    for(size_t batch=0 ; batch<batch_size ; ++batch){
        res = means[batch];
        // var = vars[batch];
        var = std::max(vars[batch],std::numeric_limits<LD>::min());
        SumIVar+=res/var;
        SumInvVar+=static_cast<LD>(1.)/var;
        SumI2Var+=res*res/var;
    }

    SumInvVar = std::max(SumInvVar,std::numeric_limits<LD>::min());

    *IntMean=SumIVar/SumInvVar;
    
    *IntSigma=static_cast<LD>(1.)/std::sqrt(SumInvVar);

    chi2=SumI2Var+(*IntMean)*(*IntMean)*SumInvVar-2*SumIVar*(*IntMean) ;

    return  chi2/(batch_size-1);
}


template<class LD>
LD plain_estimator(LD *IntMean, LD *IntSigma, const std::vector<LD>& means , const std::vector<LD>& vars){
    
    LD SumI=0;     
    LD SumI2=0;     

    size_t batch_size=means.size();
    LD res; 
    for(size_t batch=0 ; batch<batch_size ; ++batch){
        res = means[batch];
        SumI+=res;
        SumI2+=res*res;
    }

    *IntMean=SumI/batch_size;
    
    *IntSigma=std::sqrt( std::abs(SumI2 - SumI*SumI/batch_size )/(batch_size*(batch_size-1)) );

    // \chi^2 is not defined for this estimator
    return  -1;
}

#endif
