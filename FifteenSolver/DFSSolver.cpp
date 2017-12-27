#include "DFSSolver.h"
#include "FifteenBase/IFifteen.h"

#include <iostream>

bool DFSSolver::Solve()
{
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
		_checkedCount++;
		return false;
	}
}

bool DFSSolver::MoveUp()
{
	if (!_puzzle->Up()) { return false; }
	_stepsCount++;
	_visitedCount++;
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
	_stepsCount++;
	_visitedCount++;
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
	_stepsCount++;
	_visitedCount++;
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
	_stepsCount++;
	_visitedCount++;
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
