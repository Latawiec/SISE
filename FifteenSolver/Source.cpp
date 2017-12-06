#include <memory>

#include "DFSSolver.h"
#include "FifteenBase\LoggingFifteen.h"
#include "FifteenBase\Fifteen.h"

int main()
{
	using namespace FifteenBase;


	//std::shared_ptr<IFifteen> puzzle = std::make_shared<LoggingFifteen>(std::unique_ptr<IFifteen>(new Fifteen<2,2>({0,1,2,3})));
	std::shared_ptr<IFifteen> puzzle = std::make_shared<Fifteen<4, 4>>(std::vector<uint8_t>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });//; , 4, 5, 6, 7, 8});//, 9, 10, 11, 12, 13, 14, 15});

	std::vector<uint8_t> solution = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };

	std::shared_ptr<IFifteenSolver> solver = std::make_shared<DFSSolver>(puzzle, solution);

	assert(solver->IsSolved() == false);
	//puzzle->Down();
	//assert(solver->IsSolved() == true);

	bool solved = solver->Solve();
	if (solved)
	{
		std::cout << "Hurray!";
	}
	else
	{
		std::cout << "You fucking useless piece of shit!";
	}
	getchar();
	getchar();
}