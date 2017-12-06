#pragma once
#include "IFifteen.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <array>

namespace FifteenBase
{
	template<size_t Width = 4, size_t Height = 4>
	class Fifteen : public IFifteen
	{
		static_assert(Width < 256 && Height < 256, "This is way too big. Wanna make smaller one?");
	public:
		typedef std::array<uint8_t, Height*Width> PuzzleMatrix;

		Fifteen(const std::vector<uint8_t>& aData);

		virtual ~Fifteen() {}

		bool Up() override;
		bool Down() override;
		bool Left() override;
		bool Right() override;
		const uint8_t* GetMatrix() override;

		const uint8_t* GetBlankPosition() { return _blankPosition.position; }

		size_t GetSize() override { return Width*Height; }
		size_t GetWidth() override { return Width; }
		size_t GetHeight() override { return Height; }

		IFifteen* Clone()
		{
			return new Fifteen(*this);
		}

	protected:
		Fifteen(const Fifteen& aCopy)
			:
			_matrix(aCopy._matrix),
			_blankPosition(aCopy._blankPosition)
		{}

		PuzzleMatrix _matrix;
		union {
			struct {
				uint8_t x;
				uint8_t y;
			};
			uint8_t position[2];
		} _blankPosition;
	};

	template<size_t Width, size_t Height>
	inline Fifteen<Width, Height>::Fifteen(const std::vector<uint8_t>& aData)
	{
		assert(aData.size() == Width*Height);
		for (uint16_t i = 0; i < aData.size(); ++i)
		{
			if (aData[i] == 0)
			{
				_blankPosition.x = i / Width;
				_blankPosition.y = i % Height;
			}
			_matrix[i] = aData[i];
		}
	}

	template<size_t Width, size_t Height>
	inline bool Fifteen<Width, Height>::Up()
	{
		//Cannot move
		if (_blankPosition.y == 0) return false;

		std::swap(
			_matrix[_blankPosition.x + _blankPosition.y*Width],
			_matrix[_blankPosition.x + (_blankPosition.y - 1)*Width]);
		_blankPosition.y--;
		return true;
	}

	template<size_t Width, size_t Height>
	inline bool Fifteen<Width, Height>::Down()
	{
		//Cannot move
		if (_blankPosition.y == Height - 1) return false;

		std::swap(_matrix[_blankPosition.x + _blankPosition.y*Width], _matrix[_blankPosition.x + (_blankPosition.y + 1)*Width]);
		_blankPosition.y++;
		return true;
	}

	template<size_t Width, size_t Height>
	inline bool Fifteen<Width, Height>::Left()
	{
		//Cannot move
		if (_blankPosition.x == 0) return false;

		std::swap(_matrix[_blankPosition.x + _blankPosition.y*Width], _matrix[_blankPosition.x - 1 + _blankPosition.y*Width]);
		_blankPosition.x--;
		return true;
	}

	template<size_t Width, size_t Height>
	inline bool Fifteen<Width, Height>::Right()
	{
		//Cannot move
		if (_blankPosition.x == Width - 1) return false;

		std::swap(_matrix[_blankPosition.x + _blankPosition.y*Width], _matrix[_blankPosition.x + 1 + _blankPosition.y*Width]);
		_blankPosition.x++;
		return true;
	}

	template<size_t Width, size_t Height>
	inline const uint8_t* Fifteen<Width, Height>::GetMatrix()
	{
		return _matrix.data();
	}
}
