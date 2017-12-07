#pragma once
#include <stdint.h>

class IFifteenSolver
{
public:
	virtual bool		Solve() = 0;
	virtual bool		IsSolved() = 0;
	virtual size_t		GetRecursionLevel() = 0;
	virtual size_t		GetMaxReachedRecursionLevel() = 0;
	virtual size_t		GetVistedStatesCount() = 0;
	virtual size_t		GetStepsCount() = 0;
	virtual size_t		GetCheckedCount() = 0;

	virtual ~IFifteenSolver() {}
};