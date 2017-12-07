#pragma once
#include <memory>
#include <vector>

#include "boost/functional/hash.hpp"
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

	size_t		GetMaxReachedRecursionLevel() override  { return _maxReachedRecursion; }
	size_t		GetCheckedCount() override				{ return _checkedCount; }
	size_t		GetVistedStatesCount() override			{ return _visitedCount; }
	size_t		GetStepsCount() override				{ return _stepsCount; }

protected:
	FifteenSolver(std::shared_ptr<FifteenBase::IFifteen> aPuzzle, const std::vector<uint8_t>& aSolution)
		:
		_puzzle(aPuzzle),
		_solution(aSolution)
	{}

	std::shared_ptr<FifteenBase::IFifteen>	_puzzle{ nullptr };
	const std::vector<uint8_t>&				_solution;

	bool BasicCompare();
	bool SSECompare();
	bool HashCompare();

	size_t _visitedCount{};
	size_t _checkedCount{};
	size_t _stepsCount{};
	size_t _maxReachedRecursion;

	static uint32_t _maxRecursionDepth;

	virtual bool MoveUp() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool MoveDown() = 0;
};
