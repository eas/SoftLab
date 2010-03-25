#pragma once

#include "movable_object.h"
#include "map.h"

namespace game
{
	class Game;
	class Hero
		: public MovableObject
	{
		typedef MovableObject Super;
	public:
		enum Direction { up, left, down, right, none };
	public:
		Hero(Game& game, const Coords& coords);
	protected:
		virtual bool ProcessMessage(const mds::Message& message);
		virtual Coords DoMove();

	private:
		Coords direction_;

	private:
		static const unsigned period = 500;
	};
}