#pragma once

#include "mds/mds.h"
#include "map.h"

namespace game
{
	class Game;
	class MovableObject
		: public mds::Object
	{
		typedef mds::Object Super;
	public:
		MovableObject(Game& game, const Coords& coords);
		const Coords& get_coords() const;
	protected:
		virtual bool ProcessMessage(const mds::Message& message);
		virtual Coords DoMove() = 0;	// returned value must be correct
	private:
		void Move();
	private:
		Game& game_;
		Coords coords_;
	};
}