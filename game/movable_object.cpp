#include <assert.h>

#include "movable_object.h"
#include "game.h"
#include "messages.h"

namespace game
{
	MovableObject::MovableObject(Game& game, const Coords& coords)
		: Super(game),
		  game_(game),
		  coords_(coords)
	{
	}
	const Coords& MovableObject::get_coords() const
	{
		return coords_;
	}
	bool MovableObject::ProcessMessage(const mds::Message& message)
	{
		if( M_MOVE == message.get_message_id() )
		{
			Move();
			return true;
		}
		return false;
	}
	void MovableObject::Move()
	{
		coords_ = DoMove();
		game_.SendMessage( mds::Message(M_OBJECT_MOVED, NULL) );
	}
}