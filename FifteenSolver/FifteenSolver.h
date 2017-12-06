#pragma once
#include <memory>
#include <vector>

#include "IFifteenSolver.h"
#include "FifteenBase\IFifteen.h"

class FifteenSolver : public IFifteenSolver
{
public:

	enum Step : uint8_t {
		Initial,
		Up,
		Down,
		Left,
		Right
	};

	static uint32_t		MaxRecursionLevel;
	bool				IsSolved() override;

	uint32_t	GetRecursionLevel() override	{ return _recursionLevel; };
	uint32_t	GetCheckedCount() override		{ return _checkedCount; }
	uint32_t	GetChangedCount() override		{ return _changedCount; }

protected:
	FifteenSolver(std::shared_ptr<FifteenBase::IFifteen> aPuzzle, const std::vector<uint8_t>& aSolution)
		:
		_puzzle(aPuzzle),
		_solution(aSolution)
	{}

	std::shared_ptr<FifteenBase::IFifteen>	_puzzle{ nullptr };
	const std::vector<uint8_t>&				_solution;

	bool BasicCompare();

	uint32_t _changedCount{};
	uint32_t _checkedCount{};
	uint32_t _recursionLevel{};
	static uint32_t _maxRecursionDepth;

	virtual bool MoveUp() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool MoveDown() = 0;
};
