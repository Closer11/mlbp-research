#ifndef __SOLUTION_H__
#define __SOLUTION_H__


#include "problems.h"
#include "instance.h"

#include <vector>
#include <tuple>
#include <algorithm>


/*
 * Generic solution.
 * To write a solution class for a specific problem,
 * specialize this class for the corresponding problem type.
 */
template<typename ProbT>
struct Solution { };




/*****************************************************************************************/
/** Bin Packing Problem ******************************************************************/
/*****************************************************************************************/
template<>
struct Solution<BP>
{
	Solution(const Instance<BP>& inst);
	std::vector<int> item_to_bins;
	int total_bins;
	double db;  // dual bound
};

std::ostream& operator<<(std::ostream& os, const Solution<BP>& sol);




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem ******************************************************/
/*****************************************************************************************/
template<>
struct Solution<MLBP>
{
	Solution(const Instance<MLBP>& inst);
	std::vector<std::vector<int> > item_to_bins;
	int total_bin_cost;
	int db;   // dual bound, set by mip solver
};

std::ostream& operator<<(std::ostream& os, const Solution<MLBP>& sol);




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem with Fragmentation Constraints ***********************/
/*****************************************************************************************/
template<>
struct Solution<MLBPFC> : public Solution<MLBP>
{
	Solution(const Instance<MLBPFC>& inst);
	int total_penalty;
};

std::ostream& operator<<(std::ostream& os, const Solution<MLBPFC>& sol);



#endif // __SOLUTION_H__
