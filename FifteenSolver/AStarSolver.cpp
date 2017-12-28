#include "AStarSolver.h"
#include <limits>

bool AStarSolver::Solve()
{
	while (!queue.empty())
	{
		_recursionLevel = queue.top().depth + 1;
		if (_recursionLevel > _maxRecursionDepth)
		{
			queue.pop();
			continue;
		}
		_sequence[queue.top().depth] = queue.top().move;
		currentPuzzle = queue.top().Release();
		queue.pop();
		if (MoveUp()   ||
			MoveDown() ||
			MoveLeft() ||
			MoveRight()) {
			_sequence[_recursionLevel+1] = '\0';
			std::rotate(_sequence.begin(), _sequence.begin() + 1, _sequence.end());
			_stepsCount = _recursionLevel;
			return true;
		}

		_checkedCount++;

	//
	//_stepsCount++;
	//while (!queue.empty())
	//{
	//	if (Solve())
	//	{
	//		_sequence[lastDepth] = lastMove;
	//		return true;
	//	}
	//}
	}
	return false;
}

bool AStarSolver::MoveUp()
{
	if (currentPuzzle->Up())
	{
		_visitedCount++;
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			_sequence[_recursionLevel] = 'U';
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
			_sequence[_recursionLevel] = 'L';
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
			_sequence[_recursionLevel] = 'R';
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
			_sequence[_recursionLevel] = 'D';
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic, _recursionLevel, 'D' });
		currentPuzzle->Up();
	}
	return false;
}

