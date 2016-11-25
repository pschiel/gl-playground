#include "stdafx.h"
#include "Entity.h"

#ifndef GAMELIB_PLAYER
#define GAMELIB_PLAYER

class GAMELIB_API Player : public Entity
{

private:


public:

	Player();
	~Player();

	int hp;

};

#endif