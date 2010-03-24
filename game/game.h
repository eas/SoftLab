#pragma once
#include <vector>

#include "mds/mds.h"

#include "hero.h"
#include "enemy.h"
#include "map.h"

namespace game
{
	class Game
		: public mds::MessageSystem
	{
		typedef std::vector<Enemy> Enemies;
		typedef std::vector<Hero> Heroes;	// allows more than 1 hero and creation hero object during reading map
	public:
		Game();
		const Heroes get_heroes() const;
		const Enemies get_enemies() const;
	protected:
		virtual bool SystemMessageProcess(const mds::Message& message);
		virtual void IdleProcessing();
	private:
		Map map_;
		Heroes heroes_;
		Enemies enemies_;
	};
}