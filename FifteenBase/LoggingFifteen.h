#pragma once
#include <memory>
#include <iostream>

#include "IFifteen.h"

namespace FifteenBase {
	class LoggingFifteen : public IFifteen
	{
	public:
		static uint32_t objectsCount;

		LoggingFifteen(std::unique_ptr<IFifteen> aFifteen, std::ostream& aOutput = std::cout)
			: _fifteenObject(std::move(aFifteen)),
			_output(aOutput)
		{
			objectsCount++;
			std::cout << "Objects count: " << objectsCount << '\n';
		}

		~LoggingFifteen()
		{
			objectsCount--;
			_output.flush();
			//_output << "Fifteen destroyed!\n";
		}

		bool Up() override{
			if (_fifteenObject->Up()){
				_output << 'U';
				return true;
			}
			return false;
		}

		bool Down() override{
			if (_fifteenObject->Down()){
				_output << 'D';
				return true;
			}
			return false;
		}

		bool Left() override
		{
			if (_fifteenObject->Left()){
				_output << 'L';
				return true;
			}
			return false;
		}

		bool Right() override
		{
			if (_fifteenObject->Right()){
				_output << 'R';
				return true;
			}
			return false;
		}

		const uint8_t* GetMatrix() const override
		{
			const uint8_t* tableRef = _fifteenObject->GetMatrix();
			/*size_t tableWidth = _fifteenObject->GetWidth();
			size_t tableHeight = _fifteenObject->GetHeight();

			for (uint8_t x = 0; x < tableWidth; ++x)
			{
				for (uint8_t y = 0; y < tableHeight; ++y)
				{
					// + makes cout print characters as their ASCII values xD;
					_output << +tableRef[y + x*tableWidth] << ' ';
				}
				_output << '\n';
			}
			_output << '\n';*/
			return tableRef;
		}

		const size_t GetSize() const override { return _fifteenObject->GetSize(); }
		const size_t GetWidth() const override { return _fifteenObject->GetWidth(); }
		const size_t GetHeight() const override { return _fifteenObject->GetHeight(); }

		IFifteen* Clone() const override
		{
			return new LoggingFifteen(std::unique_ptr<IFifteen>(_fifteenObject->Clone()), _output);
		}

	private:
		std::unique_ptr<IFifteen> _fifteenObject = nullptr;
		std::ostream& _output;
	};
	uint32_t LoggingFifteen::objectsCount = 0;
}