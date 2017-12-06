#pragma once
#include <stdint.h>

class IFifteenSolver
{
public:
	virtual bool		Solve() = 0;
	virtual uint32_t	GetRecursionLevel() = 0;
	virtual uint32_t	GetCheckedCount() = 0;
	virtual uint32_t	GetChangedCount() = 0;
	virtual bool		IsSolved() = 0;

	virtual ~IFifteenSolver() {}
};