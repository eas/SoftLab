#include <assert.h>

#include "view.h"

#include "game.h"
#include "map.h"
#include "hero.h"
#include "enemy.h"
#include "console.h"
#include "messages.h"

namespace game
{
	View::View(game::Game& game)
		: Super(game),
		  game_(game)
	{
		symbols_[0] = ' ';
		symbols_[1] = '*';
		Post( mds::Message(M_VIEW_UPDATE, NULL), NULL );
	}
	bool View::ProcessMessage(const mds::Message& message)
	{
		assert( M_VIEW_UPDATE == message.get_message_id() );
		Update();
		Post( mds::Message(M_VIEW_UPDATE, NULL), period );
		return true;
	}
	void View::Update()
	{
		//TODO:
		static Map oldMap;
		const Map& map = game_.get_map();
		for( short i=0; i < map.get_n_rows(); ++i )
		{
			Console::GotoXY(1, i+1);
			for( short j=0; j < map.get_n_columns(); ++j )
			{
				Console::PutChar(symbols_[map(i, j)]);
			}
		}
		Coords heroCoords = game_.get_heroes()[0]->get_coords();
		Console::GotoXY( heroCoords.get_x()+1, heroCoords.get_y()+1 );
		Console::PutChar( '$' );
		
	}
}