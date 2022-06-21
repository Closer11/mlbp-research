#ifndef __MLBPFC_FORMULATION_H__
#define __MLBPFC_FORMULATION_H__


#include "problems.h"
#include "mipsolver.h"

template<typename> struct Instance;
template<typename> struct Solution;

class MLBPFCFormulation : public MIPFormulation<MLBPFC>
{
public:
	virtual void createDecisionVariables(IloEnv env, const Instance<MLBPFC>& inst);
	virtual void addConstraints(IloEnv env, IloModel model, const Instance<MLBPFC>& inst);
	virtual void addObjectiveFunction(IloEnv env, IloModel model, const Instance<MLBPFC>& inst);
	virtual void extractSolution(IloCplex cplex, const Instance<MLBPFC>& inst, Solution<MLBPFC>& sol);
private:
	// binary decision variables x_{ijk}: item/bin i at level k - 1 is inserted in bin j (=1) or not (=0) at level k;
	//									  index 0 of k is reserved for items and therefore always empty
	IloArray<IloArray<IloNumVarArray> > x;

	// binary decision variables y_{jk}: bin j is used (=1) or not (=0) at level k; 
	//									 index 0 is for items and therefore always empty
	IloArray<IloNumVarArray> y;

	// binary decision variables z_{rjk}: an item from group r is contained in bin j (=1) or not (=0) at level k;
	//									  index 0 is reserved for items and therefore always empty
	IloArray<IloArray<IloNumVarArray> > z;
};


#endif // __MLBPFC_FORMULATION_H__
