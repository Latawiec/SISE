#include "FifteenSolver.h"

uint32_t FifteenSolver::_maxRecursionDepth = 20;

bool FifteenSolver::IsSolved()
{
	return BasicCompare();
}

bool FifteenSolver::BasicCompare()
{
	const uint8_t* tablePtr = _puzzle->GetMatrix();
	const uint8_t* solutionPtr = _solution.data();
	uint32_t tableSize = _puzzle->GetSize();

	for (uint8_t i = 0; i < tableSize; ++i)
	{
		if (tablePtr[i] != solutionPtr[i]) return false;
	}
	return true;
}
