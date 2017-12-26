#pragma once
#include "FifteenSolver.h"
#include <queue>
class AStarSolver : public FifteenSolver
{
public:
	AStarSolver(std::unique_ptr<FifteenBase::IFifteen>&&				aPuzzle,
		const std::vector<uint8_t>&								aSolution,
		std::function<uint16_t(const uint8_t*, const uint8_t*, uint8_t, uint8_t, uint8_t)>	aFunction)
		:
		FifteenSolver(std::move(aPuzzle), aSolution),
		HeuristicFunction(aFunction)
	{
		uint16_t heuristic = HeuristicFunction(_puzzle->GetMatrix(), _solution.data(), _solution.size(), _puzzle->GetWidth(), _puzzle->GetHeight());
		queue.push(Node{ std::unique_ptr<FifteenBase::IFifteen>(_puzzle->Clone()), heuristic });

		//currentPuzzle = queue.top().Release();
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

	std::function<uint16_t(const uint8_t*, const uint8_t*, uint8_t, uint8_t, uint8_t)> HeuristicFunction;

	struct Node {
		mutable std::unique_ptr<FifteenBase::IFifteen>	fifteen;
		uint16_t										heuristicValue = std::numeric_limits<uint16_t>::max();

		std::unique_ptr<FifteenBase::IFifteen>&& Release() const
		{
			return std::move(fifteen);
		}

		struct Compare {
			constexpr bool operator()(const Node& left, const Node& right) const {
				return left.heuristicValue > right.heuristicValue;
			}
		};
	};

	std::priority_queue<Node, std::vector<Node>, Node::Compare> queue{ Node::Compare{} };
	std::unique_ptr<FifteenBase::IFifteen> currentPuzzle = nullptr;
};

