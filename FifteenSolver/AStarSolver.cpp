#include "AStarSolver.h"
#include <limits>

bool AStarSolver::Solve()
{
	
	if (queue.empty()) return false;
	_recursionLevel = queue.top().depth + 1;
	size_t  lastDepth = queue.top().depth - 1;
	uint8_t lastMove = queue.top().move;
	currentPuzzle = queue.top().Release();
	queue.pop();
	if (MoveUp()   ||
		MoveDown() ||
		MoveLeft() ||
		MoveRight()) {
		_sequence[lastDepth] = lastMove;
		_stepsCount++;
		return true;
	}

	_checkedCount++;

	if (_recursionLevel < _maxRecursionDepth)
	{
		_sequence[lastDepth] = lastMove;
		_stepsCount++;
		return Solve();
	}
	else {
		return false;
	}
}

bool AStarSolver::MoveUp()
{
	if (currentPuzzle->Up())
	{
		_visitedCount++;
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			_sequence[_recursionLevel-1] = 'U';
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic, _recursionLevel, 'U' });
		currentPuzzle->Down();
	}
	return false;
}

bool AStarSolver::MoveLeft()
{
	if (currentPuzzle->Left())
	{
		_visitedCount++;
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			_sequence[_recursionLevel-1] = 'L';
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic, _recursionLevel, 'L' });
		currentPuzzle->Right();
	}
	return false;
}

bool AStarSolver::MoveRight()
{
	if (currentPuzzle->Right())
	{
		_visitedCount++;
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			_sequence[_recursionLevel-1] = 'R';
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic, _recursionLevel, 'R' });
		currentPuzzle->Left();
	}
	return false;
}

bool AStarSolver::MoveDown()
{
	if (currentPuzzle->Down())
	{
		_visitedCount++;
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			_sequence[_recursionLevel-1] = 'D';
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic, _recursionLevel, 'D' });
		currentPuzzle->Up();
	}
	return false;
}

