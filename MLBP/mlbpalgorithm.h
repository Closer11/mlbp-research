#ifndef __MLBP_ALGORITHM_H__
#define __MLBP_ALGORITHM_H__


#include "problems.h"
#include "aafsolver.h"

template<typename> struct Instance;
template<typename> struct Solution;

class BFAlgorithm : public AAFAlgorithm<BF>
{
public:
	virtual void extractSolution(const Instance<MLBP>& inst, Solution<MLBP>& sol);
};

class FFAlgorithm : public AAFAlgorithm<FF>
{
public:
	virtual void extractSolution(const Instance<MLBP>& inst, Solution<MLBP>& sol);
};


#endif // __MLBP_ALGORITHM_H__
