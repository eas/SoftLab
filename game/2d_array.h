#pragma once
#include <vector>
#include <assert.h>

namespace ns_2d
{
	class Coords
	{
	public:
		Coords()
			: x_(0), y_(0)
		{
		}
		Coords( int x, int y )
			: x_(x), y_(y)
		{
		}
	public:
		void set_x(unsigned x)
		{
			x_ = x;
		}
		void set_(unsigned y)
		{
			y_ = y;
		}
		unsigned get_x() const
		{
			return x_;
		}
		unsigned get_y() const
		{
			return y_;
		}
	private:
		unsigned x_;
		unsigned y_;
	};

	template<typename T>
	class Array
	{
	public:
		Array()
			: nRows_(0),
			  nColumns_(0)
		{
		}
		Array( unsigned nRows, unsigned nColumns )
			: array_(nRows*nColumns),
			  nRows_(nRows),
			  nColumns_(nColumns)
		{
		}
		Array( unsigned nRows, unsigned nColumns, const T& defaultValue )
			: array_(nRows*nColumns, defaultValue),
			  nRows_(nRows),
			  nColumns_(nColumns)
		{
		}
		void Swap( Array<T>& other )
		{
			array_.swap(other.array_);
			std::swap(nRows_, other.nRows_);
			std::swap(nColumns_, other.nColumns_);
		}

		T& operator()(unsigned row, unsigned column)
		{
			assert(row<nRows_);
			assert(column<nColumns_);
			return array_[row*nColumns_+column];
		}
		const T& operator()(unsigned row, unsigned column) const
		{
			assert(row<nRows_);
			assert(column<nColumns_);
			return array_[row*nColumns_+column];
		}
		T& operator[](const Coords& coords)
		{
			assert(coords.get_y()<nRows_);
			assert(coords.get_x()<nColumns_);
			return array_[coords.get_y()*nColumns_+coords.get_x()];
		}
		const T& operator[](const Coords& coords) const
		{
			assert(coords.get_y()<nRows_);
			assert(coords.get_x()<nColumns_);
			return array_[coords.get_y()*nColumns_+coords.get_x()];
	}
	private:
		std::vector<T> array_;
		unsigned nRows_;
		unsigned nColumns_;
	};

}