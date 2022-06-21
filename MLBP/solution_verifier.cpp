#include "solution_verifier.h"
#include "instance.h"
#include "solution.h"
#include "users.h"

#include <sstream>
#include <algorithm>
#include <set>


/*************************************************************************************************/
/* BP ********************************************************************************************/
/*************************************************************************************************/
bool SolutionVerifier<BP>::verify(const Instance<BP>& inst, const Solution<BP>& sol, std::vector<std::string>* error_msg)
{
	bool ret = true;
	std::vector<int> levels(sol.total_bins, 0);  // size of each bin
	for (int i : inst.I) {
		int bin = sol.item_to_bins[i];
		if (bin >= sol.total_bins) {
			if (error_msg) {
				std::stringstream ss;
				ss << "Detected bin with id " << bin << " but solutions claims that there are only " << sol.total_bins << ".";
				error_msg->push_back(ss.str());
			}
			ret = false;
		} else if (bin < 0) {
			if (error_msg) {
				std::stringstream ss;
				ss << "Item " << i << " is not assigned to any bin.";
				error_msg->push_back(ss.str());
			}
			ret = false;
		} else {
			levels[bin] += inst.s[i];
		}
	}
	for (int bin = 0; bin < sol.total_bins; bin++) {
		if (levels[bin] > inst.smax) {
			if (error_msg) {
				std::stringstream ss;
				ss << "Bin " << bin << " of size " << levels[bin] << " exceeds maximum capacity (" << inst.smax << ").";
				error_msg->push_back(ss.str());
			}
			ret = false;
		}
	}
	return ret;
}


/*************************************************************************************************/
/* MLBP ******************************************************************************************/
/*************************************************************************************************/
bool SolutionVerifier<MLBP>::verify(const Instance<MLBP>& inst, const Solution<MLBP>& sol, std::vector<std::string>* error_msg)
{
	bool ret = true;
	// TODO
	std::vector<std::vector<int> > bins;
	bins.assign(inst.m + 1, std::vector<int>()); // occupied capacity of each bin
	bins[0].assign(inst.n[0], 1); // give all items a capacity of 1 to denote active
	for (int k : inst.M) if (k > 0) {
		bins[k].assign(inst.n[k], 0);
		for (int i : inst.B[k - 1]) {
			if (bins[k - 1][i] > 0) {
				int j = sol.item_to_bins[k - 1][i];
				if (j >= inst.n[k]) {
					if (error_msg) {
						std::stringstream ss;
						ss << "Detected bin with id " << j << " but solutions claims that there are only " << inst.n[k] << " bins at level " << k << ".";
						error_msg->push_back(ss.str());
					}
					ret = false;
				}
				else if (j < 0) {
					if (error_msg) {
						std::stringstream ss;
						ss << "Item/Bin " << i << " is not assigned to any bin, but solutions claims it is active.";
						error_msg->push_back(ss.str());
					}
					ret = false;
				}
				else {
					//SOUT() << "bins[" << k << "][" << j << "] += " << inst.s[k - 1][i] << std::endl;
					bins[k][j] += inst.s[k - 1][i];
				}
			}
		}
	}

	for (int k : inst.M) if (k > 0)
		for (int j : inst.B[k])
			if (bins[k][j] > inst.w[k][j]) {
				if (error_msg) {
					std::stringstream ss;
					ss << "Bin " << j << " at level " << k << " of size " << bins[k][j] << " exceeds maximum capacity(" << inst.w[k][j] << ").";
					error_msg->push_back(ss.str());
				}
				ret = false;
			}
	// NEW
	return ret;
}




/*************************************************************************************************/
/* MLBPFC ****************************************************************************************/
/*************************************************************************************************/
bool SolutionVerifier<MLBPFC>::verify(const Instance<MLBPFC>& inst, const Solution<MLBPFC>& sol, std::vector<std::string>* error_msg)
{
	bool ret = true;
	// TODO
	return ret;
}
