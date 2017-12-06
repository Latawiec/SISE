#include "DFSSolver.h"
#include "FifteenBase/IFifteen.h"

bool DFSSolver::Solve()
{
	if (IsSolved()) return true;

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
