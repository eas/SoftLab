#include <assert.h>

#include "enemy.h"
#include "game.h"

namespace game
{
	Enemy::Enemy(Game& game, const Coords& coords)
		: MovableObject(game, coords)
	{
	}
	Coords Enemy::DoMove()
	{
		return Coords();
	}
}