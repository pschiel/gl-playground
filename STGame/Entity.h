#include "stdafx.h"

#ifndef STGAME_ENTITY
#define STGAME_ENTITY

class Entity
{

private:


public:

	Entity();
	virtual ~Entity();

	float x;
	float y;
	float z;

	float rot_x; // 0-359
	float roy_y; // -90 .. 90

};

#endif