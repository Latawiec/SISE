#include "FifteenSolver.h"
#include <stdint.h>
#include <emmintrin.h>

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

bool FifteenSolver::SSECompare()
{
	__m128i* puzzleSetting = (__m128i*)_puzzle->GetMatrix();
	__m128i* solutionSetting = (__m128i*)_solution.data();

	__m128i puzzleData = _mm_load_si128(puzzleSetting);;
	__m128i solutionData = _mm_load_si128(solutionSetting);;

	__m128i cmp = _mm_cmpeq_epi8(puzzleData, solutionData);

	uint8_t result[8];
	_mm_storel_epi64((__m128i*)result, cmp);

	return result[0];
}
