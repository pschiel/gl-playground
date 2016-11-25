#include "stdafx.h"

#ifndef STGAME_CAMERA
#define STGAME_CAMERA

class Camera
{

public:

	float x;
	float y;
	float z;

	float rot_x; // 0-359
	float roy_y; // -90 .. 90

	int screen_w;
	int screen_h;

	int viewport_x;
	int viewport_y;
	int viewport_w;
	int viewport_h;

	bool follow_player;

	bool third_person;

	Camera::Camera();
	Camera::~Camera();

};

#endif