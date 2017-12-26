#include <iostream>
#include <memory>
#include <conio.h>
#include "Fifteen.h"
#include "LoggingFifteen.h"

int main()
{
	/*std::shared_ptr<FifteenBase::IFifteen> shared = std::make_shared<FifteenBase::LoggingFifteen>(std::unique_ptr<FifteenBase::IFifteen>(new FifteenBase::Fifteen<2,2>({ 0,1,2,3 })));

	assert(shared->Up() == false);
	assert(shared->Up() == false);								   
	assert(shared->Down() == true);								   
	assert(shared->Left() == false);							   
	assert(shared->Right() == true);							   
	assert(shared->Up() == true);

	std::cout << '\n';
	shared->GetMatrix();*/

	std::vector<uint8_t> initial4x4{ 1, 2, 3, 4, 0, 5, 6, 8, 9, 11, 7, 12, 13, 10, 14, 15 };
	std::vector<uint8_t> initial3x3{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	std::unique_ptr<FifteenBase::IFifteen> fifteen = std::make_unique<FifteenBase::Fifteen<3,3>>(initial3x3);
	
	uint8_t width = fifteen->GetWidth();
	uint8_t height = fifteen->GetHeight();
	const uint8_t* table = fifteen->GetMatrix();
	while (true)
	{
		for (uint8_t x = 0; x < width; ++x)
		{
			std::cout << std::flush;
			for (uint8_t y = 0; y < height; ++y)
			{
				// + makes cout print characters as their ASCII values xD;
				if (table[y + x*width] == 0)
				{
					std::cout << '#';
				}
				else
				{
					std::cout << +table[y + x*width];
				}
				std::cout << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';

		switch (_getch())
		{
		case 'w':
		case 'W':
			fifteen->Up();
			break;

		case 's':
		case 'S':
			fifteen->Down();
			break;
		case 'a':
		case 'A':
			fifteen->Left();
			break;
		case 'd':
		case 'D':
			fifteen->Right();
			break;			
		}
		system("cls");
	}
}