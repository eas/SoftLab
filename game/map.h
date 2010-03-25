#pragma once
#include <iosfwd>
#include "2d_array.h"

namespace game
{
	//TODO: maybe it would be better to do DeltaCoords class
	class Coords
	{
		friend std::ostream& operator<<(std::ostream& os, const Coords& coords);
		friend std::istream& operator>>(std::istream& is, Coords& coords);
	public:
		Coords();
		Coords(int x, int y);
		int get_x() const;
		int get_y() const;

		Coords& operator+=(const Coords& other);
		Coords& operator-=(const Coords& other);
		Coords operator+(const Coords& other) const;
		Coords operator-( const Coords& other) const;
	private:
		int x_;
		int y_;
	};

	class Map
	{
		friend std::ostream& operator<<(std::ostream& os, const Map& map);
		friend std::istream& operator>>(std::istream& is, Map& map);
	public:
		typedef enum {None, Wall} MapCell;
	private:
		typedef ns_2d::Array<MapCell> ArrayType;
	public:
		Map();
		Map(unsigned nRows, unsigned nColumns);
		MapCell& operator[](const Coords& coords);
		const MapCell& operator[](const Coords& coords) const;
		MapCell& operator()(unsigned row, unsigned column);
		const MapCell& operator()(unsigned row, unsigned column) const;
		unsigned get_n_rows() const;
		unsigned get_n_columns() const;
	private:
		bool CheckBoundary(const Coords& coords) const;
	private:
		ArrayType map_;
	};
}