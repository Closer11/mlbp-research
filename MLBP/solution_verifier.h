#ifndef __SOLUTION_VERIFIER_H__
#define __SOLUTION_VERIFIER_H__


#include <vector>
#include <string>

#include "problems.h"
#include "solution.h"


template<typename>
struct Instance;

/*
 * Generic Solution Verifier.
 * To write a solution verifier class for a specific problem,
 * specialize this class for the corresponding problem type.
 */
template<typename ProbT>
struct SolutionVerifier
{
	static bool verify(const Instance<ProbT>& inst, const Solution<ProbT>& sol, std::vector<std::string>* error_msg = nullptr);
};


/*****************************************************************************************/
/** Bin Packing Problem ******************************************************************/
/*****************************************************************************************/
template<>
struct SolutionVerifier<BP>
{
	static bool verify(const Instance<BP>& inst, const Solution<BP>& sol, std::vector<std::string>* error_msg = nullptr);
};


/*****************************************************************************************/
/** Multi-Level Bin Packing Problem ******************************************************/
/*****************************************************************************************/
template<>
struct SolutionVerifier<MLBP>
{
	static bool verify(const Instance<MLBP>& inst, const Solution<MLBP>& sol, std::vector<std::string>* error_msg = nullptr);
};


/*****************************************************************************************/
/** Multi-Level Bin Packing Problem with Fragmentation Constraints ***********************/
/*****************************************************************************************/
template<>
struct SolutionVerifier<MLBPFC>
{
	static bool verify(const Instance<MLBPFC>& inst, const Solution<MLBPFC>& sol, std::vector<std::string>* error_msg = nullptr);
};

#endif // __SOLUTION_VERIFIER_H__
