#include "DFSSolver.h"
#include "FifteenBase/IFifteen.h"

#include <iostream>

std::unordered_set<size_t> DFSSolver::_savedStates = {};

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
	if (/*_savedStates.size()*/_recursionLevel >= _maxRecursionDepth) { return false; }
	if (IsSolved())
	{
		return true;
	}
	_recursionLevel++;
	
	// Check if such item was already found before
	
	size_t hash = boost::hash_range(_puzzle->GetMatrix(), _puzzle->GetMatrix() + _puzzle->GetSize());
	if (DFSSolver::_savedStates.find(hash) != DFSSolver::_savedStates.end()){
		//return false;
	}
	DFSSolver::_savedStates.insert(hash);
	

	if ( MoveLeft() || MoveRight() || MoveUp() || MoveDown() )
	{
		return true;
	}
	else
	{
		DFSSolver::_savedStates.erase(hash);
		_recursionLevel--;
		return false;
	}
}

bool DFSSolver::MoveUp()
{
	if (/*_lastStep == FifteenSolver::Step::Down ||*/ !_puzzle->Up()) { return false; }
	FifteenSolver::Step rememberedLastStep = _lastStep;
	_visitedCount++;
	_stepsCount++;
	_lastStep = FifteenSolver::Step::Up;
	if (Solve())
	{
		return true;
	}
	else
	{
		_stepsCount--;
		_lastStep = rememberedLastStep;
		_puzzle->Down();
		return false;
	}
}

bool DFSSolver::MoveDown()
{
	if (/*_lastStep == FifteenSolver::Step::Up ||*/ !_puzzle->Down()) { return false; }
	FifteenSolver::Step rememberedLastStep = _lastStep;
	_visitedCount++;
	_stepsCount++;
	_lastStep = FifteenSolver::Step::Down;
	if (Solve())
	{
		return true;
	}
	else
	{
		_stepsCount--;
		_lastStep = rememberedLastStep;
		_puzzle->Up();
		return false;
	}
}

bool DFSSolver::MoveLeft()
{
	if (/*_lastStep == FifteenSolver::Step::Right ||*/ !_puzzle->Left()) { return false; }
	FifteenSolver::Step rememberedLastStep = _lastStep;
	_visitedCount++;
	_stepsCount++;
	_lastStep = FifteenSolver::Step::Left;
	if (Solve())
	{
		return true;
	}
	else
	{
		_stepsCount--;
		_lastStep = rememberedLastStep;
		_puzzle->Right();
		return false;
	}
}

bool DFSSolver::MoveRight()
{
	if (/*_lastStep == FifteenSolver::Step::Left ||*/ !_puzzle->Right()) { return false; }
	FifteenSolver::Step rememberedLastStep = _lastStep;
	_visitedCount++;
	_stepsCount++;
	_lastStep = FifteenSolver::Step::Right;
	if (Solve())
	{
		return true;
	}
	else
	{
		_stepsCount--;
		_lastStep = rememberedLastStep;
		_puzzle->Left();
		return false;
	}
}
