#include <assert.h>

#include "game.h"
#include "messages.h"
#include "console.h"

namespace game
{
	Game::Game()
	{
	}

	bool Game::SystemMessageProcess(const mds::Message& message)
	{
		if( M_EXIT == message.get_message_id() )
		{
			return true;
		}
		return false;
	}

	void Game::IdleProcessing()
	{
		assert( 0 != heroes_.size() );

		if( Console::IsKeyPressed() )
		{
			Console::Key key = Console::GetPressedKey();
			switch( key )
			{
			case keys::esc:
				SendMessage( mds::Message(M_EXIT, NULL) );
				break;
			case keys::left:
				heroes_[0].Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::left)) );
				break;
			case keys::right:
				heroes_[0].Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::right)) );
				break;
			case keys::down:
				heroes_[0].Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::down)) );
				break;
			case keys::up:
				heroes_[0].Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::up)) );
				break;
			}
		}
	}
}