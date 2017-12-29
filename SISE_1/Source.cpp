#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

#include "FifteenSolver\DFSSolver.h"
#include "FifteenSolver\BFSSolver.h"
#include "FifteenSolver\AStarSolver.h"
#include "FifteenBase\Fifteen.h"

using namespace std;
//bfs rlud 4x4_01_00001.txt dupa dupa

#define SOLUTION4x4 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 }

std::vector<uint8_t> solution = SOLUTION4x4;

std::unique_ptr<IFifteenSolver> DFS(const char * arg, const char * filename)
{
	std::fstream input(filename);
	std::vector<uint8_t> initial{};

	if (input.is_open())
	{
		uint16_t w, h, value;
		input >> w >> h;
		for (uint16_t i = 0; i < w*h; ++i)
		{
			input >> value;
			initial.push_back(value);
		}
	}
	input.close();

	std::unique_ptr<FifteenBase::IFifteen> puzzle = std::make_unique<FifteenBase::Fifteen<4, 4> >(initial);

	return std::make_unique<DFSSolver>(std::move(puzzle), solution, arg);
}

std::unique_ptr<IFifteenSolver> BFS(const char * arg, const char * filename)
{

	std::fstream input(filename);
	std::vector<uint8_t> initial{};

	if (input.is_open())
	{
		uint16_t w, h, value;
		input >> w >> h;
		for (uint16_t i = 0; i < w*h; ++i)
		{
			input >> value;
			initial.push_back(value);
		}
	}
	input.close();

	std::unique_ptr<FifteenBase::IFifteen> puzzle = std::make_unique<FifteenBase::Fifteen<4, 4> >(initial);

	return std::make_unique<BFSSolver>(std::move(puzzle), solution, arg);
}

std::unique_ptr<IFifteenSolver> AStar(const char * arg, const char * filename)
{
	std::fstream input(filename);
	std::vector<uint8_t> initial{};

	if (input.is_open())
	{
		uint16_t w, h, value;
		input >> w >> h;
		for (uint16_t i = 0; i < w*h; ++i)
		{
			input >> value;
			initial.push_back(value);
		}
	}
	input.close();

	std::unique_ptr<FifteenBase::IFifteen> puzzle = std::make_unique<FifteenBase::Fifteen<4, 4> >(initial);

	if (!strcmp(arg , "hamm"))
	{
		return std::make_unique<AStarSolver>(std::move(puzzle), solution,
			[](const uint8_t* tabA, const uint8_t* tabB, uint8_t size, uint8_t width = 0, uint8_t height = 0)->uint16_t
			{
				//Hamming
				uint16_t result{};
				while (0 <-- size)
				{
					if (tabA[size] != tabB[size]) result++;
				}
				return result;
			});
	}
	else
	{
		return std::make_unique<AStarSolver>(std::move(puzzle), solution,
			[](const uint8_t* tabA, const uint8_t* tabB, uint8_t size, uint8_t width = 0, uint8_t height = 0)->uint16_t
			{
				//Manhatan
				uint16_t result{};
				for(uint8_t i = 0; i<size; ++i)
				{
					uint16_t distance;
					for(uint8_t j = 0; j<size; ++j)
					{
						if(tabA[i] == tabB[j])
						{
							distance = std::abs(j - i);
							result += (distance / width + distance % height);
						}
					}
				}
				return result;
			});
	}
}

vector<string> Parse(const string& aCommand) {
	size_t pos = 0;
	size_t lastPos = 0;
	vector<string> result{};
	while (pos != aCommand.size())
	{
		pos = aCommand.find(" ");
		result.push_back(aCommand.substr(lastPos, pos));
		lastPos = pos;
	}
	return result;
}

int main(int count, char * argv[])
{
	std::unique_ptr<IFifteenSolver> solver = nullptr;
	
	if (!strcmp(argv[1], "dfs"))
	{
		solver = DFS(argv[2], argv[3]);
	}
	else if (!strcmp(argv[1], "bfs"))
	{
		solver = BFS(argv[2], argv[3]);
	}
	else if (!strcmp(argv[1], "astr"))
	{
		solver = AStar(argv[2], argv[3]);
	}

	bool solved;

	auto start = std::chrono::system_clock::now();
	solved = solver->Solve();
	auto end = std::chrono::system_clock::now();

	std::fstream outSolution(argv[4], fstream::out);
	if (outSolution.is_open())
	{
		if (solved)
		{
			outSolution << solver->GetStepsCount() << '\n' << solver->GetSteps().data();
		}
		else
		{
			outSolution << -1;
		}
	}
	outSolution.close();

	std::fstream outData(argv[5], fstream::out);
	if (outData.is_open())
	{
		if (solved)
		{
			outData << solver->GetStepsCount() << '\n';
		}
		else
		{
			outData << -1 << '\n';
		}
		outData << solver->GetVistedStatesCount() << '\n'
			<< solver->GetCheckedCount() << '\n'
			<< 0 << '\n'
			<< std::chrono::duration<double, std::milli>(end - start).count();
	}
	outData.close();
}