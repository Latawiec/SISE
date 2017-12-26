#include <memory>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include "DFSSolver.h"
#include "BFSSolver.h"
#include "AStarSolver.h"
#include "FifteenBase\LoggingFifteen.h"
#include "FifteenBase\Fifteen.h"

std::mutex StopReport;

std::chrono::system_clock::time_point start;
std::chrono::system_clock::time_point end;

bool Solved;

void Report(IFifteenSolver* aSolver, FifteenBase::IFifteen* aPuzzle, bool* isDone)
{
	std::lock_guard<std::mutex> lock(StopReport);

	const uint8_t* puzzleTable = aPuzzle->GetMatrix();
	const uint8_t puzzleWidth = aPuzzle->GetWidth();
	const uint8_t puzzleHeight = aPuzzle->GetHeight();

	uint8_t i = 0;
	while (!*isDone)
	{
		std::cout << '\r';
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		i++;
		i %= 4;
		switch (i)
		{
		case 0: std::cout << '-'; break;
		case 1: std::cout << '\\'; break;
		case 2: std::cout << '|'; break;
		case 3: std::cout << '/'; break;
		}
		std::cout << ' ' << "Time elapsed: " << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count();
	}
	std::cout << '\n';
	if (Solved)
	{
		std::cout << "Solution schema: \n";
		for (uint8_t x = 0; x < puzzleWidth; ++x)
		{
			std::cout << std::flush;
			for (uint8_t y = 0; y < puzzleHeight; ++y)
			{
				// + makes cout print characters as their ASCII values xD;
				std::cout << +puzzleTable[y + x*puzzleWidth] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	else
	{
		std::cout << "No solution found :(((((((((( \n";
	}
	std::cout << ' ' << "Total time elapsed: " << std::chrono::duration<double>(end - start).count() << '\n';
	std::cout << "Steps to given solution: "	<< aSolver->GetStepsCount() << '\n';
	std::cout << "Total states visited: "		<< aSolver->GetVistedStatesCount() << '\n';
	std::cout << "Total states processed: "		<< aSolver->GetCheckedCount() << '\n';
	std::cout << "Steps to the solution: "		<< aSolver->GetSteps().data() << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(10));
}
#define SOLUTION4x4 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 }
#define SOLUTION3x3 { 1, 2, 3, 4, 5, 6, 7, 8, 0 }
#define SOLUTION2x2 { 3, 2, 1, 0 }

#define INITIAL4x4 {	1,	3,	0,	4,	\
						5,	2,	7,	8,	\
						9,	6,	10, 12,	\
						13, 14, 11, 15 }
//#define INITIAL4x4 {	1,	2,	3,	4,	\
//						5,	6,	7,	8,	\
//						9,	10,	11, 0,	\
//						13, 14, 15, 12 }
#define INITIAL3x3 { 1, 2, 3, 4, 8, 5, 7, 6, 0 }
int main()
{
	using namespace FifteenBase;


	//std::shared_ptr<IFifteen> puzzle = std::make_shared<LoggingFifteen>(std::unique_ptr<IFifteen>(new Fifteen<3,3>({0,1,2,3,4,5,6,7,8})));
	std::unique_ptr<IFifteen> puzzle = std::make_unique<Fifteen<4, 4>>(std::vector<uint8_t>INITIAL4x4);

	std::vector<uint8_t> solution = SOLUTION4x4;
	IFifteen* puzzleHandle = puzzle.get();
	std::unique_ptr<IFifteenSolver> solver = std::make_unique<DFSSolver>(std::move(puzzle), solution, "rdul");
	
	//std::shared_ptr<IFifteenSolver> solver = std::make_shared<AStarSolver>(std::move(puzzle), solution, [](const uint8_t* tabA, const uint8_t* tabB, uint8_t size, uint8_t width = 0, uint8_t height = 0)->uint16_t
	//{
	//	//Hamming
	//	uint16_t result{};
	//	while (0 <-- size)
	//	{
	//		if (tabA[size] != tabB[size]) result++;
	//	}
	//	return result;
	//});

	//std::shared_ptr<IFifteenSolver> solver = std::make_shared<AStarSolver>(std::move(puzzle), solution, [](const uint8_t* tabA, const uint8_t* tabB, uint8_t size, uint8_t width = 0, uint8_t height = 0)->uint16_t
	//{
	//	//Manhatan
	//	uint16_t result{};
	//	for(uint8_t i = 0; i<size; ++i)
	//	{
	//		uint16_t distance;
	//		for(uint8_t j = 0; j<size; ++j)
	//		{
	//			if(tabA[i] == tabB[j])
	//			{
	//				distance = std::abs(j - i);
	//				result += (distance / width + distance % height);
	//			}
	//		}
	//	}
	//	return result;
	//});

	assert(solver->IsSolved() == false);
	//puzzle->Down();
	//assert(solver->IsSolved() == true);

	bool isDone = false;
	std::thread t(std::bind(&Report, solver.get(), puzzleHandle, &isDone));
	t.detach();
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	start = std::chrono::system_clock::now();
	Solved = solver->Solve();
	end = std::chrono::system_clock::now();
	isDone = true;

	{ // Sycnhronize trheads
		std::lock_guard<std::mutex> lock(StopReport);
	}

	getchar();
}