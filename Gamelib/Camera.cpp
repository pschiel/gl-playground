#define GAMELIB_EXPORTS
#include "stdafx.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/core/func_trigonometric.hpp>
#define _USE_MATH_DEFINES
#include "math.h"


Camera::Camera()
{
	
	x = -3.0f;
	y = 2.0f;
	z = -3.0f;

	rot_x = 0.0f;
	rot_y = 0.785f;

	fov = 45.0f;

	viewport_x = 0;
	viewport_y = 0;
	viewport_w = 1280;
	viewport_h = 800;

}


Camera::~Camera()
{
}


void Camera::lookat(float tx, float ty, float tz)
{

	float dxz = glm::length(glm::vec2(tx-x, tz-z));
	rot_y = atan2(tx-x, tz-z);
	rot_x = atan2(ty-y, dxz);

	printf("rot x %f y %f\n", rot_x, rot_y);

}
