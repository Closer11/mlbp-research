#ifndef __AAF_SOLVER_H__
#define __AAF_SOLVER_H__

//#include <ilcplex/ilocplex.h>
#include "problems.h"
#include "algorithms.h"

#include<memory>


template<typename> struct Instance;
template<typename> struct Solution;

template<typename AlgT>
class AAFAlgorithm
{
public:
	virtual void addUserCallbacks(const Instance<MLBP>& inst) { }
	virtual void extractSolution(const Instance<MLBP>& inst, Solution<MLBP>& sol) = 0;
};


template<typename AlgT>
class NullAlgorithm : public AAFAlgorithm<AlgT>
{
public:
	virtual void addUserCallbacks(const Instance<MLBP>& inst) { }
	virtual void extractSolution(const Instance<MLBP>& inst, Solution<MLBP>& sol) { }
};


/**
 * Generic AAF Approximation Algorithm Solver.
 * Subclass from AAFAlgorithm to write an AAF approximation algorithm.
 */
template<typename AlgT>
class AAFSolver
{
public:
	AAFSolver();
	~AAFSolver();

	template<typename T, typename... Args>
	void setAlgorithm(Args... args)
	{
		algorithm = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	T* getAlgorithm() const { return dynamic_cast<T*>(algorithm.get()); }

	void setTimeLimit(int time) { m_time_limit = time; }
	void setThreads(int number) { m_threads = number; }

	void run(const Instance<MLBP>& inst, Solution<MLBP>& sol);

protected:

private:
	std::unique_ptr<AAFAlgorithm<AlgT> > algorithm;
	int m_time_limit;  // in seconds -> 0: no time limit
	int m_threads;     // number of used threads, 0: default setting
};

#endif // __AAF_SOLVER_H__

