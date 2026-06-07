#ifndef VEGAS_IntBatch
#define VEGAS_IntBatch
#include"VEGAS_IntTot.hpp"



// Integrate using batches. 
// I use the estimator provided by 
// G. PETER LEPAGE JOURNAL  OF COMPUTATIONAL A New Algorithm PHYSICS 27, 192-203 (1978)
// Seems to wotk fine!

template<class LD, int NDim, int NBin, int NBinInit, BatchEstimator Estimator, class RandEn>
LD VEGAS<LD,NDim,NBin,NBinInit,Estimator,RandEn>::IntegrateBatch(LD *IntMean, LD *IntSigma){
    std::vector<LD> means(NBatches);
    std::vector<LD> vars(NBatches);

    for(int batch = 0; batch < NBatches; ++batch) { IntegrateTot(&means[batch], &vars[batch]); }

    return batch_estimator(IntMean,IntSigma,means,vars);
}






#endif