#pragma once
#include "mds/mds.h"

namespace game
{
	class Game;
	class View
		: public mds::Object
	{
		typedef mds::Object Super;
	public:
		View(Game& game);
	protected:
		virtual bool ProcessMessage( const mds::Message& message );
	private:
		void Update();

	private:
		// TODO: it's already in mds::Object, what to do?
		Game& game_;
		//TODO: change to something like std::map
		int symbols_[2];
		static const unsigned period = 250;
	};
}