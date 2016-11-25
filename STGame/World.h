#include "stdafx.h"
#include <map>
#include "Player.h"
#include "Mob.h"
#include "Entity.h"
#include "Mapdata.h"

#ifndef STGAME_WORLD
#define STGAME_WORLD


class World
{

public:

	std::map<long, Player*> players;
	std::map<long, Mob*> mobs;
	std::map<long, Entity*> entities;
	Mapdata mapdata;

	World();
	~World();

};

#endif