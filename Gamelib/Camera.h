#include "stdafx.h"

#ifndef GAMELIB_CAMERA
#define GAMELIB_CAMERA

class GAMELIB_API Camera
{

public:

	float x;
	float y;
	float z;

	float rot_x;
	float rot_y;

	float fov;

	int viewport_x;
	int viewport_y;
	int viewport_w;
	int viewport_h;

	Camera::Camera();
	Camera::~Camera();

	void Camera::lookat(float x, float y, float z);

};

#endif