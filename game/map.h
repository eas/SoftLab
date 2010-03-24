#pragma once
#include <iosfwd>
#include "2d_array.h"

namespace game
{
	//TODO: maybe it would be better to do DeltaCoords class
	class Coords
	{
	public:
		Coords();
		Coords(int x, int y);
		int get_x() const;
		int get_y() const;
	private:
		int x_;
		int y_;
	};

	class Map
	{
		friend std::ostream& operator<<(std::ostream& os, const Map& map);
		friend std::istream& operator>>(std::istream& is, Map& map);
	public:
		typedef enum {Wall, None} MapCell;
	private:
		typedef ns_2d::Array<MapCell> ArrayType;
	public:
		Map();
		Map(unsigned nRows, unsigned nColumns);
		MapCell& operator[](const Coords& coords);
		const MapCell& operator[](const Coords& coords) const;
	private:
		bool CheckBoundary(const Coords& coords) const;
		MapCell& operator()(unsigned row, unsigned column);
	private:
		ArrayType map_;
	};
}