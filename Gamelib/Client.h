#include "stdafx.h"
#include <SDL.h>
#include <boost/thread.hpp>
#include "World.h"
#include "Camera.h"
#include "Settings.h"

#ifndef GAMELIB_CLIENT
#define GAMELIB_CLIENT

class GAMELIB_API Client {

private:

	SDL_Window *_window;
	SDL_GLContext _glcontext;
	boost::thread *_input_thread;
	boost::thread *_render_thread;
	std::string _state;

	void input_thread();
	void render_thread();

public:

	Settings settings;
	World world;
	Camera camera;

	Client();
	~Client();

	void start();
	void stop();
	void restart();

	void sleep(int seconds);
	std::string getState();

};

#endif

