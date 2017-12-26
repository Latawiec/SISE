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

		virtual const uint8_t*	GetMatrix() const = 0;

		virtual const size_t GetSize() const = 0;
		virtual const size_t GetWidth() const = 0;
		virtual const size_t GetHeight() const = 0;

		virtual ~IFifteen(){}

		virtual IFifteen* Clone() const = 0;
	};
}
