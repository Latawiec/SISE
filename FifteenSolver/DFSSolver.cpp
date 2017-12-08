#include "DFSSolver.h"
#include "FifteenBase/IFifteen.h"

#include <iostream>

//#define KURWA_MAC

bool DFSSolver::Solve()
{
#ifdef KURWA_MAC
	std::cout << "Current State: \n";
	const uint8_t* puzzleTable = _puzzle->GetMatrix();
	uint8_t puzzleWidth = _puzzle->GetWidth();
	uint8_t puzzleHeight = _puzzle->GetHeight();

	for (uint8_t x = 0; x < puzzleWidth; ++x)
	{
		std::cout << std::flush;
		for (uint8_t y = 0; y < puzzleHeight; ++y)
		{
			// + makes cout print characters as their ASCII values xD;
			std::cout << +puzzleTable[y + x*puzzleWidth] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
#endif

	_checkedCount++;
	if (_recursionLevel > _maxRecursionDepth) { return false; }
	if (IsSolved())
	{
		return true;
	}
	_recursionLevel++;
	
	if ( _moves[0]() || _moves[1]() || _moves[2]() || _moves[3]() )
	{
		return true;
	}
	else
	{
		_recursionLevel--;
		return false;
	}
}

bool DFSSolver::MoveUp()
{
	if (!_puzzle->Up()) { return false; }
	_visitedCount++;
	_stepsCount++;
	if (Solve())
	{
		_sequence[--_recursionLevel] = 'U';
		return true;
	}
	else
	{
		_stepsCount--;
		_puzzle->Down();
		return false;
	}
}

bool DFSSolver::MoveDown()
{
	if (!_puzzle->Down()) { return false; }
	_visitedCount++;
	_stepsCount++;
	if (Solve())
	{
		_sequence[--_recursionLevel] = 'D';
		return true;
	}
	else
	{
		_stepsCount--;
		_puzzle->Up();
		return false;
	}
}

bool DFSSolver::MoveLeft()
{
	if (!_puzzle->Left()) { return false; }
	_visitedCount++;
	_stepsCount++;
	if (Solve())
	{
		_sequence[--_recursionLevel] = 'L';
		return true;
	}
	else
	{
		_stepsCount--;
		_puzzle->Right();
		return false;
	}
}

bool DFSSolver::MoveRight()
{
	if (!_puzzle->Right()) { return false; }
	_visitedCount++;
	_stepsCount++;
	if (Solve())
	{

		_sequence[--_recursionLevel] = 'R';
		return true;
	}
	else
	{
		_stepsCount--;
		_puzzle->Left();
		return false;
	}
}
