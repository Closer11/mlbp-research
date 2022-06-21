#include "instance.h"
#include "solution.h"
#include "lib/util.h"
#include "users.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <cassert>



/*************************************************************************************************/
/* BP ********************************************************************************************/
/*************************************************************************************************/
Instance<BP>::Instance(const std::string& input_file) : filename(input_file)
{
	std::ifstream file(input_file);
	if (!file.is_open())
		throw std::runtime_error("Cannot open file!");

	file >> n >> smax;

	I.reserve(n);
	s.assign(n, -1);
	for (int i = 0; i < n; i++) {
		I.push_back(i);
		file >> s[i];
	}
}

int Instance<BP>::objective(const Solution<BP>& sol) const
{
	return sol.total_bins;
}


std::ostream& operator<<(std::ostream& os, const Instance<BP> &inst)
{
	os << "n=" << inst.s.size() << ", smax=" << inst.smax << ", s=" << inst.s;
	return os;
}




/*************************************************************************************************/
/* MLBP ******************************************************************************************/
/*************************************************************************************************/
Instance<MLBP>::Instance(const std::string& input_file) : filename(input_file)
{
	std::ifstream file(input_file);
	if (!file.is_open())
		throw std::runtime_error("Cannot open file!");

	read_instance(file);
}

void Instance<MLBP>::read_instance(std::ifstream& file)
{
	// reading data from the file
	file >> m;

	// read number of items and bins for each level
	n.assign(m+1, 0);
	M.reserve(m);
	for (int i = 0; i < m+1; i++) {
		if (i != 0) M.push_back(i);
		file >> n[i];
	}

	// read item sizes and bin sizes for each level
	s.assign(m+1, std::vector<int>());
	B.assign(m+1, std::vector<int>());
	for (int i = 0; i < m+1; i++) {
		s[i].assign(n[i], 0);
		for (int j = 0; j < n[i]; j++) {
			B[i].push_back(j);
			file >> s[i][j];
		}
	}

	// read capacities of bins for each level
	w.assign(m+1, std::vector<int>());
	for (int i = 1; i < m+1; i++) {
		w[i].assign(n[i], 0);
		for (int j = 0; j < n[i]; j++)
			file >> w[i][j];
	}

	// read cost of each bin for each level
	c.assign(m+1, std::vector<int>());
	for (int i = 1; i < m+1; i++) {
		c[i].assign(n[i], 0);
		for (int j = 0; j < n[i]; j++)
			file >> c[i][j];
	}
}

int Instance<MLBP>::objective(const Solution<MLBP>& sol) const
{
	return sol.total_bin_cost;
}

std::ostream& operator<<(std::ostream& os, const Instance<MLBP> &inst)
{
	os << "m=" << inst.m << ", n=" << inst.n;
	return os;
}




/*************************************************************************************************/
/* MLBPFC ****************************************************************************************/
/*************************************************************************************************/
Instance<MLBPFC>::Instance(const std::string& input_file) : Instance<MLBP>()
{
	filename = input_file;

	std::ifstream file(input_file);
	if (!file.is_open())
		throw std::runtime_error("Cannot open file!");

	read_instance(file);

	file >> p >> q;
	q = int(n[0] * q / 100);
	g.reserve(n[0]);
	int gj;
	for (int i = 0; i < n[0]; i++) {
		file >> gj;
		g.push_back(gj-1);
	}
}

int Instance<MLBPFC>::objective(const Solution<MLBPFC>& sol) const
{
	return sol.total_bin_cost + sol.total_penalty;
}

std::ostream& operator<<(std::ostream& os, const Instance<MLBPFC> &inst)
{
	os << "m=" << inst.m << ", n=" << inst.n << ", q=" << inst.q << ", p=" << inst.p << "\n";
	os << "g=" << inst.g;
	return os;
}

