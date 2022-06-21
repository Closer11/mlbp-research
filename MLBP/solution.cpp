#include "solution.h"

#include "lib/util.h"
#include "users.h"

#include <algorithm>
#include <numeric>
#include <cassert>



/*****************************************************************************************/
/** Bin Packing Problem ******************************************************************/
/*****************************************************************************************/
Solution<BP>::Solution(const Instance<BP>& inst) : item_to_bins(inst.s.size())
{
	std::iota(item_to_bins.begin(), item_to_bins.end(), 0);
	total_bins = (int)inst.s.size();
}

std::ostream& operator<<(std::ostream& os, const Solution<BP>& sol)
{
	os << sol.item_to_bins;
	return os;
}




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem ******************************************************/
/*****************************************************************************************/
Solution<MLBP>::Solution(const Instance<MLBP>& inst) : item_to_bins(inst.m)
{
	total_bin_cost = 0;
	for (int k : inst.M) if (k > 0) {
		std::iota(item_to_bins[k - 1].begin(), item_to_bins[k - 1].end(), 0);
		for (int j : inst.B[k]) total_bin_cost += inst.c[k][j];
	}
}

std::ostream& operator<<(std::ostream& os, const Solution<MLBP>& sol) {
	for (std::vector<int> e : sol.item_to_bins) os << e;
	return os;
}




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem with Fragmentation Constraints ***********************/
/*****************************************************************************************/
Solution<MLBPFC>::Solution(const Instance<MLBPFC>& inst) : Solution<MLBP>(inst)
{
	// max penalty is when every top-level bin contains items from every group
	total_penalty = inst.q * inst.n[inst.m] * inst.p;
}

std::ostream& operator<<(std::ostream& os, const Solution<MLBPFC>& sol) {
	for (std::vector<int> e : sol.item_to_bins) os << e;
	return os;
}


