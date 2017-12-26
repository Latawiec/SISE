#include "AStarSolver.h"
#include <limits>

bool AStarSolver::Solve()
{
	_recursionLevel++;
	if (queue.empty()) return false;

	currentPuzzle = queue.top().Release();
	queue.pop();
	if (MoveUp() ||
		MoveDown() ||
		MoveLeft() ||
		MoveRight()) {
		return true;
	}

	if (_recursionLevel < _maxRecursionDepth)
	{
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
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic });
		currentPuzzle->Down();
	}
	return false;
}

bool AStarSolver::MoveLeft()
{
	if (currentPuzzle->Left())
	{
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic });
		currentPuzzle->Right();
	}
	return false;
}

bool AStarSolver::MoveRight()
{
	if (currentPuzzle->Right())
	{
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic });
		currentPuzzle->Left();
	}
	return false;
}

bool AStarSolver::MoveDown()
{
	if (currentPuzzle->Down())
	{
		uint16_t heuristic = HeuristicFunction(currentPuzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());

		if (heuristic == 0) {
			return true;
		}
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(currentPuzzle->Clone()), heuristic });
		currentPuzzle->Up();
	}
	return false;
}

