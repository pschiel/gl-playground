#include "stdafx.h"
#include "Player.h"
#include "Mob.h"
#include "Entity.h"

#ifndef GAMELIB_WORLD
#define GAMELIB_WORLD

class GAMELIB_API World
{


public:

	std::map<long, Player *> players;
	std::map<long, Mob *> mobs;
	std::map<long, Entity *> entities;

	World();
	~World();

	void load(const char *filename);

};

#endif