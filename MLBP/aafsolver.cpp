#include "aafsolver.h"


#include "solution.h"
#include "solution_verifier.h"
#include "instance.h"
#include "users.h"

#include "lib/util.h"

#include <stdexcept>
#include <algorithm>

//ILOSTLBEGIN

template<typename AlgT>
AAFSolver<AlgT>::AAFSolver() : m_time_limit(0), m_threads(0)
{
	algorithm = std::make_unique<NullAlgorithm<AlgT> >();
}

template<typename AlgT>
AAFSolver<AlgT>::~AAFSolver() { }

template<typename AlgT>
typename void AAFSolver<AlgT>::run(const Instance<MLBP>& inst, Solution<MLBP>& sol)
{
	try {
		algorithm->addUserCallbacks(inst);

		algorithm->extractSolution( inst, sol);
		MIP_OUT(TRACE) << "Solution: \n" << sol << std::endl;
	}
	catch (std::exception& e) {
		throw std::runtime_error(e.what());
	}
	catch (...) {
		throw std::runtime_error("Unknown exception");
	}
}

template class AAFSolver<BF>;
template class AAFSolver<FF>;

