#include <memory>

#include "DFSSolver.h"
#include "FifteenBase\LoggingFifteen.h"
#include "FifteenBase\Fifteen.h"

int main()
{
	using namespace FifteenBase;

	std::shared_ptr<IFifteen> puzzle = std::make_shared<LoggingFifteen>(std::unique_ptr<IFifteen>(new Fifteen<3,3>({0,1,2,3,4,5,6,7,8})));

	std::vector<uint8_t> solution = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	std::shared_ptr<IFifteenSolver> solver = std::make_shared<DFSSolver>(puzzle, solution);

	assert(solver->IsSolved() == false);
	//puzzle->Down();
	//assert(solver->IsSolved() == true);


	solver->Solve();
}