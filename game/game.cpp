#include <assert.h>
#include <fstream>

#include "game.h"
#include "messages.h"
#include "console.h"

namespace game
{
	Game::Game()
	{
	}
	Game::~Game()
	{
		for( Heroes::iterator iter = heroes_.begin(); iter != heroes_.end(); ++iter )
		{
			delete (*iter);
		}
		for( Enemies::iterator iter = enemies_.begin(); iter != enemies_.end(); ++iter )
		{
			delete (*iter);
		}
	}
	void Game::Start()
	{
		for( Heroes::iterator iter = heroes_.begin(); iter != heroes_.end(); ++iter )
		{
			(*iter)->Post( mds::Message(M_MOVE, NULL), initialDelay );
		}
		for( Enemies::iterator iter = enemies_.begin(); iter != enemies_.end(); ++iter )
		{
			(*iter)->Post( mds::Message(M_MOVE, NULL), initialDelay );
		}
		Super::Loop();

	}
	void Game::LoadMap(const char* fileName)
	{
		std::fstream file(fileName);
		file >> map_;

		Coords coords;
		file >> coords;
		heroes_.push_back( new Hero(*this, coords) );
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
			int key = Console::GetPressedKey();
			switch( key )
			{
			case keys::esc:
				SendMessage( mds::Message(M_EXIT, NULL) );
				break;
			case keys::left:
				heroes_[0]->Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::left)) );
				break;
			case keys::right:
				heroes_[0]->Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::right)) );
				break;
			case keys::down:
				heroes_[0]->Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::down)) );
				break;
			case keys::up:
				heroes_[0]->Send( mds::Message(M_CHANGE_DIRECTION, reinterpret_cast<mds::Message::Data>(Hero::up)) );
				break;
			}
		}
	}

	const Game::Heroes& Game::get_heroes() const
	{
		return heroes_;
	}
	const Game::Enemies& Game::get_enemies() const
	{
		return enemies_;
	}
	const Map& Game::get_map() const
	{
		return map_;
	}
}