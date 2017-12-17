#pragma once
#include "FifteenSolver.h"
class AStarSolver : public FifteenSolver
{
public:
	AStarSolver(std::shared_ptr<FifteenBase::IFifteen>					aPuzzle,
				const std::vector<uint8_t>&								aSolution,
				std::function<uint16_t(const uint8_t*, const uint8_t*, uint8_t)>	aFunction)
		:
		FifteenSolver(aPuzzle, aSolution),
		HeuristicFunction(aFunction)
	{
		_maxRecursionDepth = 30;
		_sequence = std::vector<unsigned char>(_maxRecursionDepth);
		_moveset[0] = std::bind(&AStarSolver::MoveUp,		this);
		_moveset[1] = std::bind(&AStarSolver::MoveDown,		this);
		_moveset[2] = std::bind(&AStarSolver::MoveLeft,		this);
		_moveset[3] = std::bind(&AStarSolver::MoveRight,	this);
	}

	AStarSolver() = delete;
	AStarSolver(AStarSolver&) = delete;

	~AStarSolver()
	{};

	bool Solve() override;

protected:
	bool MoveUp() override;
	bool MoveDown() override;
	bool MoveLeft() override;
	bool MoveRight() override;

	uint16_t CheckUp();
	uint16_t CheckDown();
	uint16_t CheckLeft();
	uint16_t CheckRight();

	union HeuristicValues {
		uint16_t values[4];
		struct {
			uint16_t up;
			uint16_t down;
			uint16_t left;
			uint16_t right;
		};
	};

	std::function<bool()> _moveset[4];
	uint16_t _lastSmallesHeuristic = 65535;
	std::function<uint16_t(const uint8_t*, const uint8_t*, uint8_t)> HeuristicFunction;
};

