#include "mlbpalgorithm.h"

#include "instance.h"
#include "solution.h"
#include "users.h"


void BFAlgorithm::extractSolution(const Instance<MLBP>& inst, Solution<MLBP>& sol)
{
	// for each item/bin (sorted by index) assign item to the bin such that the remaining capacity is minimised
	std::vector<std::vector<int> > a;
	a.assign(inst.m + 1, std::vector<int>());
	std::vector<std::vector<int> > c = inst.w;

	sol.total_bin_cost = 0;
	a[0].assign(inst.n[0], 1);
	for (int k : inst.M) if (k > 0) {
		a[k].assign(inst.n[k], 0);
		sol.item_to_bins[k - 1].assign(inst.n[k - 1], -1);

		// with pre-processing items
		std::vector<int> items = inst.B[k - 1];
		std::sort(items.begin(), items.end(), [&](int t1, int t2) { 
			return inst.s[k - 1][t2] < inst.s[k - 1][t1]; 
		}); for (int i : items) if (a[k - 1][i] == 1) { //*/

		/*/ without pre-processing items
		for (int i : inst.B[k - 1]) if (a[k - 1][i] == 1) { //*/
			//SOUT() << "size: " << inst.s[k - 1][i] << std::endl;
			int min_value = INT_MAX;
			int min_index = -1;

			// with pre-processing bins
			std::vector<int> bins = inst.B[k];
			std::sort(bins.begin(), bins.end(), [&](int t1, int t2) {
				//return inst.w[k][t2] < inst.w[k][t1];
				return inst.c[k][t1] < inst.c[k][t2];
			}); for (int j : bins) { //*/

			/*/ without pre-processing bins
			for (int j : inst.B[k]) { //*/
				//SOUT() << "capacity: " << c[k][j] << std::endl;
				int remainder = c[k][j] - inst.s[k - 1][i];
				if (remainder >= 0 && remainder < min_value) {
					min_value = remainder;
					min_index = j;
				}
			}

			//SOUT() << "min_index: " << min_index << std::endl;
			if (min_index < 0) continue;

			sol.item_to_bins[k - 1][i] = min_index;
			c[k][min_index] -= inst.s[k - 1][i];
			a[k][min_index] = 1;
		}

		for (int j : inst.B[k])
			sol.total_bin_cost += a[k][j] * inst.c[k][j];
	}
}

