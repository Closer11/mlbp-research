#ifndef __INSTANCE_H__
#define __INSTANCE_H__


#include <string>
#include <vector>
#include <iostream>

#include "problems.h"


template<typename>
struct Solution;


/*
 * Generic problem instance class.
 * To write an instance class for a specific problem,
 * speialize this class for the corresponding problem type.
 */
template<typename ProbT>
struct Instance { };




/*****************************************************************************************/
/** Bin Packing Problem ******************************************************************/
/*****************************************************************************************/
template<>
struct Instance<BP>
{
	friend std::ostream& operator<<(std::ostream& os, const Instance<BP>& inst);

	Instance(const std::string& input_file);

	int objective(const Solution<BP>& sol) const;

	std::string filename;

	int n;              // number of items
	std::vector<int> I; // index set of items [0,...,n-1]
	std::vector<int> s; // size of items
	int smax;           // maximum bin size
};

std::ostream& operator<<(std::ostream& os, const Instance<BP>& inst);




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem ******************************************************/
/*****************************************************************************************/
template<>
struct Instance<MLBP>
{
	friend std::ostream& operator<<(std::ostream& os, const Instance<MLBP>& inst);

	Instance(const std::string& input_file);

	int objective(const Solution<MLBP>& sol) const;

	std::string filename;

	int m;               // number of levels
	std::vector<int> n;  // number of items/bins at each level; level 0: number of items, level > 0: number of bins

	std::vector<std::vector<int> > s;  // size of each item/bin at each level
	std::vector<std::vector<int> > w;  // capacity of each bin;  index 0 is reserved for items and therefore always empty
	std::vector<std::vector<int> > c;  // cost of each bin;      index 0 is reserved for items and therefore always empty

	std::vector<int> M;                // index set of levels 1...m;  [1,...,m]
	std::vector<std::vector<int> > B;  // index set of items/bins for each level

protected:
	Instance() { }
	void read_instance(std::ifstream& file);
};

std::ostream& operator<<(std::ostream& os, const Instance<MLBP>& inst);




/*****************************************************************************************/
/** Multi-Level Bin Packing Problem with Fragmentation Constraints ***********************/
/*****************************************************************************************/
template<>
struct Instance<MLBPFC> : public Instance<MLBP>
{
	friend std::ostream& operator<<(std::ostream& os, const Instance<MLBPFC>& inst);

	Instance(const std::string& input_file);

	int objective(const Solution<MLBPFC>& sol) const;

	int q; // number of groups
	int p; // penalty factor
	std::vector<int> g; // group of each item
};

std::ostream& operator<<(std::ostream& os, const Instance<MLBPFC>& inst);


#endif // __INSTANCE_H__
