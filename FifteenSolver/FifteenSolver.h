#pragma once
#include <memory>
#include <vector>

#include "boost/functional/hash.hpp"
#include "IFifteenSolver.h"
#include "FifteenBase/IFifteen.h"

class FifteenSolver : public IFifteenSolver
{
public:
	bool				IsSolved() override;

	size_t		GetRecursionLevel() override			{ return _recursionLevel; }
	size_t		GetMaxReachedRecursionLevel() override  { return _maxReachedRecursion; }
	size_t		GetCheckedCount() override				{ return _checkedCount; }
	size_t		GetVistedStatesCount() override			{ return _visitedCount; }
	size_t		GetStepsCount() override				{ return _stepsCount; }
	const std::vector<unsigned char>& GetSteps() override { return _sequence; }

protected:
	FifteenSolver(std::unique_ptr<FifteenBase::IFifteen>&& aPuzzle, const std::vector<uint8_t>& aSolution, uint32_t aMaxRecursion = 30)
		:
		_puzzle(std::move(aPuzzle)),
		_solution(aSolution),
		_maxRecursionDepth(aMaxRecursion),
		_sequence(aMaxRecursion)
	{}

	std::unique_ptr<FifteenBase::IFifteen>	_puzzle{ nullptr };
	const std::vector<uint8_t>&				_solution;

	bool BasicCompare();
	bool SSECompare();

	size_t _visitedCount{};
	size_t _checkedCount{};
	size_t _stepsCount{};
	size_t _recursionLevel{};
	size_t _maxReachedRecursion;
	std::vector<unsigned char> _sequence;

	uint32_t _maxRecursionDepth;

	virtual bool MoveUp() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool MoveDown() = 0;
};
