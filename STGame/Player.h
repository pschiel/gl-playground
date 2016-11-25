#include "stdafx.h"
#include "Entity.h"

#ifndef STGAME_PLAYER
#define STGAME_PLAYER

class Player : public Entity
{

private:


public:

	Player();
	~Player();

	int hp;

};

#endif