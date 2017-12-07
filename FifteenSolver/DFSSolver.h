#pragma once
#include <memory>
#include <vector>
#include <unordered_set>
#include "boost/functional/hash.hpp"
#include "FifteenSolver.h"

class DFSSolver : public FifteenSolver
{
public:
	DFSSolver(std::shared_ptr<FifteenBase::IFifteen> aPuzzle, const std::vector<uint8_t>& aSolution, FifteenSolver::Step aLastStep = FifteenSolver::Step::Initial)
		:
		FifteenSolver(aPuzzle, aSolution),
		_lastStep(aLastStep)
	{
		_maxRecursionDepth =  5000;
	}

	~DFSSolver()
	{};

	bool		Solve() override;

protected:

	bool MoveUp() override;
	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveDown() override;

private:
	FifteenSolver::Step _lastStep;
	static std::unordered_set<size_t> _savedStates;
};

