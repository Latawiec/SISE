#include "BFSSolver.h"
#include <iostream>
bool BFSSolver::Solve()
{
	if(IsSolved()) return true;
	while (_recursionLevel < _maxRecursionDepth)
	{
		_currentDepth = 0;
		_checkedCount = 0;
		++_recursionLevel;
		if (_moves[0]() || _moves[1]() || _moves[2]() || _moves[3]())
		{
			_visitedCount += _currentDepth;
			return true;
		}
	}
}

bool BFSSolver::MoveUp()
{
	if (!_puzzle->Up()) { return false; }
	++_currentDepth;
	
	if (_currentDepth == _recursionLevel){
		_visitedCount++;
		if (IsSolved()){
			_stepsCount++;
			_sequence[--_currentDepth] = 'U';
			return true;
		}
	}
	else
	{
		_checkedCount++;
		if (_movesWithoutDown[0]() || _movesWithoutDown[1]() || _movesWithoutDown[2]()){
			_stepsCount++;
			_sequence[--_currentDepth] = 'U';
			return true;
		}
	}
	_puzzle->Down();
	--_currentDepth;
	return false;
}

bool BFSSolver::MoveLeft()
{
	if (!_puzzle->Left()) { return false; }
	++_currentDepth;

	if (_currentDepth == _recursionLevel) {
		_visitedCount++;
		if (IsSolved()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'L';
			return true;
		}
	}
	else
	{
		_checkedCount++;
		if (_movesWithoutRight[0]() || _movesWithoutRight[1]() || _movesWithoutRight[2]()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'L';
			return true;
		}
	}
	_puzzle->Right();
	--_currentDepth;
	return false;
}

bool BFSSolver::MoveRight()
{
	if (!_puzzle->Right()) { return false; }
	++_currentDepth;

	if (_currentDepth == _recursionLevel) {
		_visitedCount++;
		if (IsSolved()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'R';
			return true;
		}
	}
	else
	{
		_checkedCount++;
		if (_movesWithoutLeft[0]() || _movesWithoutLeft[1]() || _movesWithoutLeft[2]()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'R';
			return true;
		}
	}
	_puzzle->Left();
	--_currentDepth;
	return false;
}

bool BFSSolver::MoveDown()
{
	if (!_puzzle->Down()) { return false; }
	++_currentDepth;

	if (_currentDepth == _recursionLevel) {
		_visitedCount++;
		if (IsSolved()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'D';
			return true;
		}
	}
	else
	{
		_checkedCount++;
		if (_movesWithoutUp[0]() || _movesWithoutUp[1]() || _movesWithoutUp[2]()) {
			_stepsCount++;
			_sequence[--_currentDepth] = 'D';
			return true;
		}
	}
	_puzzle->Up();
	--_currentDepth;
	return false;
}
