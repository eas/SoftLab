#include <assert.h>

#include "hero.h"
#include "game.h"
#include "messages.h"

namespace game
{
	Hero::Hero(Game& game, const Coords& coords)
		: Super(game, coords),
		  direction_(0, 0)
	{
	}

	//TODO: void DoMove()
	Coords Hero::DoMove()
	{
		Post( mds::Message(M_MOVE, NULL), period );
		Coords temp = get_coords() + direction_;
		if( Map::None == game_.get_map()[temp] )
		{
			return get_coords() + direction_;
		}
		else
		{
			direction_ = Coords(0, 0);
			return get_coords();
		}
	}

	bool Hero::ProcessMessage(const mds::Message& message)
	{
		if( !Super::ProcessMessage(message) )
		{
			if( M_CHANGE_DIRECTION == message.get_message_id() )
			{
				unsigned data = reinterpret_cast<int>( message.get_data() );
				switch( data )
				{
				case up:
					direction_ = Coords(-1, 0);
					break;
				case down:
					direction_ = Coords(1, 0);
					break;
				case right:
					direction_ = Coords(0, 1);
					break;
				case left:
					direction_ = Coords(0, -1);
					break;
				}
				return true;
			}
			return false;
		}
		else
		{
			return true;
		}
	}
}