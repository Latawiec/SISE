#pragma once
#include <stdint.h>

namespace FifteenBase
{
	class IFifteen
	{
	public:
		virtual bool			Up() = 0;
		virtual bool			Down() = 0;
		virtual bool			Left() = 0;
		virtual bool			Right() = 0;

		virtual const uint8_t*	GetMatrix() = 0;

		virtual size_t GetSize() = 0;
		virtual size_t GetWidth() = 0;
		virtual size_t GetHeight() = 0;

		virtual ~IFifteen(){}

		virtual IFifteen* Clone() = 0;
	};
}
