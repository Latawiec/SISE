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
		_maxRecursionDepth = 15;
	}

	~DFSSolver()
	{
		_savedStates.erase(_hash);
	};

	bool		Solve() override;

protected:

	bool MoveUp() override;
	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveDown() override;

private:
	FifteenSolver::Step _lastStep;
	size_t _hash{};
	static std::unordered_set<size_t> _savedStates;
};

