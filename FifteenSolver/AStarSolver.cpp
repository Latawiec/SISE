#include "AStarSolver.h"
#include <limits>

bool AStarSolver::Solve()
{
	if (_recursionLevel > _maxRecursionDepth)
	{
		return false;
	}
	_recursionLevel++;
	uint8_t indices[] = { 0,1,2,3 };
	HeuristicValues heuristicResult;
	{
		if ((heuristicResult.up = CheckUp()) == 0 ||
			(heuristicResult.down = CheckDown()) == 0 ||
			(heuristicResult.left = CheckLeft()) == 0 ||
			(heuristicResult.right = CheckRight()) == 0)
		{
			return true;
		}

		std::sort(indices, indices + 4, [&heuristicResult](const uint8_t a, const uint8_t b) { return heuristicResult.values[a] < heuristicResult.values[b]; });
	}
	
	if (heuristicResult.values[indices[0]] >= _lastSmallesHeuristic) { _recursionLevel--; return false; }
	uint16_t rememberedHeuristic = _lastSmallesHeuristic;
	_lastSmallesHeuristic = heuristicResult.values[indices[0]];

	for (uint8_t i = 0; i<4; ++i)
	{
		if (heuristicResult.values[indices[i]] != std::numeric_limits<uint16_t>::max())
		{
			if (_moveset[indices[i]]())
			{
				return true;
			}
		}
	}
	_lastSmallesHeuristic = rememberedHeuristic;
	_recursionLevel--;
	return false;
}

bool AStarSolver::MoveUp()
{
	_puzzle->Up();

	if (Solve())
	{
		_checkedCount++;
		_sequence[--_recursionLevel] = 'U';
		return true;
	}
	_puzzle->Down();
	return false;
}

bool AStarSolver::MoveLeft()
{
	_puzzle->Left();

	if (Solve())
	{
		_checkedCount++;
		_sequence[--_recursionLevel] = 'L';
		return true;
	}
	_puzzle->Right();
	return false;
}

bool AStarSolver::MoveRight()
{
	_puzzle->Right();

	if (Solve())
	{
		_checkedCount++;
		_sequence[--_recursionLevel] = 'R';
		return true;
	}
	_puzzle->Left();
	return false;
}

bool AStarSolver::MoveDown()
{
	_puzzle->Down();

	if (Solve())
	{
		_checkedCount++;
		_sequence[--_recursionLevel] = 'D';
		return true;
	}
	_puzzle->Up();
	return false;
}

uint16_t AStarSolver::CheckUp()
{
	_visitedCount++;
	if (!_puzzle->Up()) { return std::numeric_limits<uint16_t>::max(); }

	uint16_t heuristic = HeuristicFunction(_puzzle->GetMatrix(), _solution.data(), _solution.size());

	if (heuristic == 0)
	{
		_sequence[--_recursionLevel] = 'U';
		return 0;
	}
	_puzzle->Down();
	return heuristic;
}

uint16_t AStarSolver::CheckDown()
{
	_visitedCount++;
	if (!_puzzle->Down()) { return std::numeric_limits<uint16_t>::max(); }

	uint16_t heuristic = HeuristicFunction(_puzzle->GetMatrix(), _solution.data(), _solution.size());

	if (heuristic == 0)
	{
		_sequence[--_recursionLevel] = 'D';
		return 0;
	}
	_puzzle->Up();
	return heuristic;
}

uint16_t AStarSolver::CheckLeft()
{
	_visitedCount++;
	if (!_puzzle->Left()) { return std::numeric_limits<uint16_t>::max(); }

	uint16_t heuristic = HeuristicFunction(_puzzle->GetMatrix(), _solution.data(), _solution.size());

	if (heuristic == 0)
	{
		_sequence[--_recursionLevel] = 'L';
		return 0;
	}
	_puzzle->Right();
	return heuristic;
}

uint16_t AStarSolver::CheckRight()
{
	_visitedCount++;
	if (!_puzzle->Right()) { return std::numeric_limits<uint16_t>::max(); }

	uint16_t heuristic = HeuristicFunction(_puzzle->GetMatrix(), _solution.data(), _solution.size());

	if (heuristic == 0)
	{
		_sequence[--_recursionLevel] = 'R';
		return 0;
	}
	_puzzle->Left();
	return heuristic;
}

