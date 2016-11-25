#define GAMELIB_EXPORTS
#include "stdafx.h"
#include <boost/python.hpp>
#include "Client.h"
#include "Server.h"
#include "World.h"
#include "Player.h"
#include "Mob.h"
#include "Entity.h"


using namespace boost::python;

BOOST_PYTHON_MODULE(gamelib)
{

    class_<Client>("Client")
        .def("start", &Client::start)
        .def("stop", &Client::stop)
        .def("restart", &Client::restart)
		.def("sleep", &Client::sleep)
		.def_readwrite("world", &Client::world)
		.def_readwrite("camera", &Client::camera)
		.add_property("state", &Client::getState)
	;

	class_<Server>("Server")
    ;

	class_<World>("World")
		.def("load", &World::load)
		.def_readwrite("players", &World::players)
		.def_readwrite("mobs", &World::mobs)
		.def_readwrite("entities", &World::entities)
    ;

	class_<Player>("Player")
    ;

	class_<Mob>("Mob")
    ;

	class_<Entity>("Entity")
    ;

	class_<Camera>("Camera")
		.def_readwrite("x", &Camera::x)
		.def_readwrite("y", &Camera::y)
		.def_readwrite("z", &Camera::z)
		.def_readwrite("rot_x", &Camera::rot_x)
		.def_readwrite("rot_y", &Camera::rot_y)
		.def_readwrite("fov", &Camera::fov)
		.def_readwrite("viewport_x", &Camera::viewport_x)
		.def_readwrite("viewport_y", &Camera::viewport_y)
		.def_readwrite("viewport_w", &Camera::viewport_w)
		.def_readwrite("viewport_h", &Camera::viewport_h)
		.def("lookat", &Camera::lookat)
    ;

}
