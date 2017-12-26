#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <unordered_set>

#include "FifteenSolver.h"

class DFSSolver : public FifteenSolver
{
public:
	DFSSolver(std::unique_ptr<FifteenBase::IFifteen>&& aPuzzle, const std::vector<uint8_t>& aSolution, const std::string& aMoveset)
		:
		FifteenSolver(std::move(aPuzzle), aSolution)
	{
		assert(aMoveset.size() == 4);
		for (uint8_t i = 0; i < 4; ++i)
		{
			switch (aMoveset[i])
			{
			case 'l':
			case 'L':
				_moves[i] = std::bind(&DFSSolver::MoveLeft, this);
				break;
			case 'r':
			case 'R':
				_moves[i] = std::bind(&DFSSolver::MoveRight, this);
				break;
			case 'u':
			case 'U':
				_moves[i] = std::bind(&DFSSolver::MoveUp, this);
				break;
			case 'd':
			case 'D':
				_moves[i] = std::bind(&DFSSolver::MoveDown, this);
				break;
			}
		}
	}

	~DFSSolver()
	{};

	bool Solve() override;

protected:

	bool MoveUp() override;
	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveDown() override;

private:
	std::function<bool()> _moves[4];
};

