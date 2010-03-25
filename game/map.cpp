#include <iostream>
#include "map.h"

namespace game
{
	Coords::Coords()
		: x_(0),
		  y_(0)
	{
	}
	Coords::Coords(int x, int y)
		: x_(x),
		  y_(y)
	{
	}
	int Coords::get_x() const
	{
		return x_;
	}
	int Coords::get_y() const
	{
		return y_;
	}

	Coords& Coords::operator+=(const Coords& other)
	{
		x_ += other.x_;
		y_ += other.y_;
		return *this;
	}
	Coords& Coords::operator-=(const Coords& other)
	{
		x_ -= other.x_;
		y_ -= other.y_;
		return *this;
	}
	Coords Coords::operator+(const Coords& other) const
	{
		Coords temp(*this);
		temp += other;
		return temp;
	}
	Coords Coords::operator-(const Coords& other) const
	{
		Coords temp(*this);
		temp -= other;
		return temp;
	}
	Map::Map()
	{
	}

	Map::Map(unsigned nRows, unsigned nColumns)
		: map_(nRows, nColumns, None)
	{
	}

	Map::MapCell& Map::operator[](const Coords& coords)
	{
		CheckBoundary(coords);
		return map_(coords.get_y(), coords.get_x());
	}
	const Map::MapCell& Map::operator[](const Coords& coords) const
	{
		CheckBoundary(coords);
		return map_(coords.get_y(), coords.get_x());
	}
	Map::MapCell& Map::operator()(unsigned row, unsigned column)
	{
		return map_(row, column);
	}
	const Map::MapCell& Map::operator()(unsigned row, unsigned column) const
	{
		return map_(row, column);
	}
	bool Map::CheckBoundary(const Coords& coords) const
	{
		return (coords.get_y() < map_.get_n_rows()) && (coords.get_x() < map_.get_n_columns());
	}

	unsigned Map::get_n_rows() const
	{
		return map_.get_n_rows();
	}
	unsigned Map::get_n_columns() const
	{
		return map_.get_n_columns();
	}

	std::istream& operator>>(std::istream& is, Map::MapCell& cell)
	{
		int temp;
		is >> temp;
		if( 0 == temp )
			cell = Map::None;
		else
			cell = Map::Wall;
		return is;
	}
	//std::ostream& operator<<(std::ostream& os, const Map::MapCell& cell)
	//{
	//	os << static_cast<int>(cell);
	//	os << " ";
	//	return os;
	//}

	std::istream& operator>>(std::istream& is, Coords& coords)
	{
		is >> coords.x_ >> coords.y_;
		return is;
	}

	std::istream& operator>>(std::istream& is, Map& map)
	{
		unsigned nRows, nColumns;
		is >> nRows >> nColumns;

		Map::ArrayType temp(nRows, nColumns);

		for( unsigned i=0; i<nRows; ++i )
		{
			for( unsigned j=0; j<nColumns; ++j )
			{
				is >> temp(i, j);
			}
		}

		map.map_.Swap(temp);
		return is;
	}
	std::ostream& operator<<(std::ostream& os, const Map& map)
	{
		unsigned nRows = map.map_.get_n_rows();
		unsigned nColumns = map.map_.get_n_columns();
		os << nRows << " " << nColumns << std::endl;
		for( unsigned i=0; i<nRows; ++i )
		{
			for( unsigned j=0; j<nColumns; ++j )
			{
				os << map.map_(i, j);
			}
		}
		return os;
	}
}