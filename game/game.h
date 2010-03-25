#pragma once
#include <vector>

#include "mds/mds.h"

#include "hero.h"
#include "enemy.h"
#include "map.h"
#include "view.h"

namespace game
{
	class Game
		: public mds::MessageSystem
	{
		typedef mds::MessageSystem Super;
	public:
		//TODO: ref type
		typedef std::vector<Enemy*> Enemies;
		typedef std::vector<Hero*> Heroes;	// allows more than 1 hero and creation hero object during reading map
	public:
		Game();
		virtual ~Game();
		void Start();
		void LoadMap(const char* fileName);
		const Heroes& get_heroes() const;
		const Enemies& get_enemies() const;
		const Map& get_map() const;
	protected:
		virtual bool SystemMessageProcess(const mds::Message& message);
		virtual void IdleProcessing();
	private:
		void Loop();	// hide to prevent call
	private:
		Map map_;
		Heroes heroes_;
		Enemies enemies_;

		static const unsigned initialDelay = 300;
	};
}