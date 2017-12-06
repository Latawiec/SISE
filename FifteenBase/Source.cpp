#include <iostream>
#include <memory>

#include "Fifteen.h"
#include "LoggingFifteen.h"

int main()
{
	std::shared_ptr<FifteenBase::IFifteen> shared = std::make_shared<FifteenBase::LoggingFifteen>(std::unique_ptr<FifteenBase::IFifteen>(new FifteenBase::Fifteen<2,2>({ 0,1,2,3 })));

	assert(shared->Up() == false);
	assert(shared->Up() == false);								   
	assert(shared->Down() == true);								   
	assert(shared->Left() == false);							   
	assert(shared->Right() == true);							   
	assert(shared->Up() == true);

	std::cout << '\n';
	shared->GetMatrix();
}