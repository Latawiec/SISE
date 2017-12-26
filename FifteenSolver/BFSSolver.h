#pragma once

#include <functional>
#include "FifteenSolver.h"

class BFSSolver : public FifteenSolver
{
public:
	BFSSolver(std::unique_ptr<FifteenBase::IFifteen>&& aPuzzle, const std::vector<uint8_t>& aSolution, const std::string& aMoveset)
		:
		FifteenSolver(std::move(aPuzzle), aSolution)
	{
		assert(aMoveset.size() == 4);
		uint8_t leftIndex{}, rightIndex{}, upIndex{}, downIndex{};
		for (uint8_t i = 0; i < 4; ++i)
		{
			switch (aMoveset[i])
			{
			case 'l':
			case 'L':
				_moves[i] = std::bind(&BFSSolver::MoveLeft, this);
				_movesWithoutDown.get(downIndex++)		= &_moves[i];
				_movesWithoutUp.get(upIndex++)			= &_moves[i];
				_movesWithoutRight.get(rightIndex++)	= &_moves[i];
				break;
			case 'r':
			case 'R':
				_moves[i] = std::bind(&BFSSolver::MoveRight, this);
				_movesWithoutDown.get(downIndex++)		= &_moves[i];
				_movesWithoutUp.get(upIndex++)			= &_moves[i];
				_movesWithoutLeft.get(leftIndex++)		= &_moves[i];
				break;
			case 'u':
			case 'U':
				_moves[i] = std::bind(&BFSSolver::MoveUp, this);
				_movesWithoutDown.get(downIndex++)		= &_moves[i];
				_movesWithoutLeft.get(leftIndex++)		= &_moves[i];
				_movesWithoutRight.get(rightIndex++)	= &_moves[i];
				break;
			case 'd':
			case 'D':
				_moves[i] = std::bind(&BFSSolver::MoveDown, this);
				_movesWithoutLeft.get(leftIndex++)		= &_moves[i];
				_movesWithoutUp.get(upIndex++)			= &_moves[i];
				_movesWithoutRight.get(rightIndex++)	= &_moves[i];
				break;
			}
		}
	}
	~BFSSolver()
	{};

	bool Solve() override;

protected:

	bool MoveUp() override;
	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveDown() override;

private:
	std::function<bool()> _moves[4];
	struct{
		std::function<bool()>*& get(uint8_t index)
		{
			return moves[index];
		}
		const std::function<bool()>& operator[](uint8_t index)
		{
			return *moves[index];
		}
		std::function<bool()>* moves[3];
	}_movesWithoutUp,
	 _movesWithoutDown,
	 _movesWithoutLeft,
	 _movesWithoutRight;

	uint16_t _currentDepth = 0;
};

