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
		typedef enum { up, left, down, right, none } Direction;
	public:
		Hero(Game& game, const Coords& coords);
	protected:
		virtual bool ProcessMessage(const mds::Message& message);
		virtual Coords DoMove();

	private:
		Coords direction_;
	};
}