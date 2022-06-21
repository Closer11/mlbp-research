#ifndef __MLBP_FORMULATION_H__
#define __MLBP_FORMULATION_H__


#include "problems.h"
#include "mipsolver.h"

template<typename> struct Instance;
template<typename> struct Solution;

class MLBPFormulation : public MIPFormulation<MLBP>
{
public:
	virtual void createDecisionVariables(IloEnv env, const Instance<MLBP>& inst);
	virtual void addConstraints(IloEnv env, IloModel model, const Instance<MLBP>& inst);
	virtual void addObjectiveFunction(IloEnv env, IloModel model, const Instance<MLBP>& inst);
	virtual void extractSolution(IloCplex cplex, const Instance<MLBP>& inst, Solution<MLBP>& sol);
private:
	// binary decision variables x_{ijk}: item/bin i at level k - 1 is inserted in bin j (=1) or not (=0) at level k;
	//									  index 0 of k is reserved for items and therefore always empty
	IloArray<IloArray<IloNumVarArray>> x;

	// binary decision variables y_{jk}: bin j is used (=1) or not (=0) at level k; 
	//									 index 0 is for items and therefore always empty
	IloArray<IloNumVarArray> y;
};


class NF_MLBPFormulation : public MIPFormulation<MLBP>
{
public:
	virtual void createDecisionVariables(IloEnv env, const Instance<MLBP>& inst);
	virtual void addConstraints(IloEnv env, IloModel model, const Instance<MLBP>& inst);
	virtual void addObjectiveFunction(IloEnv env, IloModel model, const Instance<MLBP>& inst);
	virtual void extractSolution(IloCplex cplex, const Instance<MLBP>& inst, Solution<MLBP>& sol);
private:
	// binary decision variables x_{ijk}: item/bin i at level k - 1 is inserted in bin j (=1) or not (=0) at level k;
	//									  index 0 of k is reserved for items and therefore always empty
	IloArray<IloArray<IloNumVarArray>> x;

	// binary decision variables y_{jk}: bin j is used (=1) or not (=0) at level k; 
	//									 index 0 is for items and therefore always empty
	IloArray<IloNumVarArray> y;

	// integer decision variables f_{ijk}: amount of flow (=0 and m) between item/bin i at level k - 1 and bin j at level k
	IloArray<IloArray<IloNumVarArray>> f;
};


#endif // __MLBP_FORMULATION_H__
