#pragma once
#include <memory>
#include <vector>

#include "FifteenSolver.h"

class DFSSolver : public FifteenSolver
{
public:
	DFSSolver(std::shared_ptr<FifteenBase::IFifteen> aPuzzle, const std::vector<uint8_t>& aSolution, FifteenSolver::Step aLastStep = FifteenSolver::Step::Initial)
		:
		FifteenSolver(aPuzzle, aSolution),
		_lastStep(aLastStep)
	{}

	~DFSSolver() {};

	bool		Solve() override;

protected:

	bool MoveUp() override;
	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveDown() override;

private:
	FifteenSolver::Step _lastStep;
};

