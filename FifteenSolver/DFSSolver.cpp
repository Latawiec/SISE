#include "DFSSolver.h"
#include "FifteenBase/IFifteen.h"

#include <iostream>

std::unordered_set<size_t> DFSSolver::_savedStates = {};

bool DFSSolver::Solve()
{
	if (IsSolved())
	{
		std::cout << '\n';
		const uint8_t* tableRef = _puzzle->GetMatrix();
		size_t tableWidth = _puzzle->GetWidth();
		size_t tableHeight = _puzzle->GetHeight();

		for (uint8_t x = 0; x < tableWidth; ++x)
		{
			for (uint8_t y = 0; y < tableHeight; ++y)
			{
				// + makes cout print characters as their ASCII values xD;
				std::cout << +tableRef[y + x*tableWidth] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';

		std::cout << "Hania mac!";
		return true;
	}
	if (_savedStates.size() >= _maxRecursionDepth)return false;
	{ // Check if such item was already found before

		boost::hash_range(_hash, _puzzle->GetMatrix(), _puzzle->GetMatrix() + _puzzle->GetSize());

		if (DFSSolver::_savedStates.find(_hash) != DFSSolver::_savedStates.end()){
			return false;
		}
		
		DFSSolver::_savedStates.insert(_hash);
	}

	return MoveRight() || MoveUp() || MoveDown() || MoveLeft();
}

bool DFSSolver::MoveUp()
{
	std::shared_ptr<FifteenBase::IFifteen>	puzzle = std::shared_ptr<FifteenBase::IFifteen>(_puzzle->Clone());

	if( _lastStep == FifteenSolver::Step::Down || !puzzle->Up() ) return false;
	return DFSSolver(puzzle, _solution, FifteenSolver::Step::Up).Solve();
}

bool DFSSolver::MoveDown()
{
	std::shared_ptr<FifteenBase::IFifteen>	puzzle = std::shared_ptr<FifteenBase::IFifteen>(_puzzle->Clone());

	if (_lastStep == FifteenSolver::Step::Up || !puzzle->Down()) return false;
	return DFSSolver(puzzle, _solution, FifteenSolver::Step::Down).Solve();
}

bool DFSSolver::MoveLeft()
{
	std::shared_ptr<FifteenBase::IFifteen>	puzzle = std::shared_ptr<FifteenBase::IFifteen>(_puzzle->Clone());

	if (_lastStep == FifteenSolver::Step::Right || !puzzle->Left()) return false;
	return DFSSolver(puzzle, _solution, FifteenSolver::Step::Left).Solve();
}

bool DFSSolver::MoveRight()
{
	std::shared_ptr<FifteenBase::IFifteen>	puzzle = std::shared_ptr<FifteenBase::IFifteen>(_puzzle->Clone());

	if (_lastStep == FifteenSolver::Step::Left || !puzzle->Right()) return false;
	return DFSSolver(puzzle, _solution, FifteenSolver::Step::Right).Solve();
}
