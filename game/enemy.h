#pragma once

#include "movable_object.h"

namespace game
{
	class Game;
	class Enemy
		: public MovableObject
	{
		typedef MovableObject Super;
	public:
		Enemy(Game& game, const Coords& coords);
	protected:
		virtual Coords DoMove();
	};
}