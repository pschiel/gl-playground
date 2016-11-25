#include "stdafx.h"

#ifndef GAMELIB_ENTITY
#define GAMELIB_ENTITY

class GAMELIB_API Entity
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