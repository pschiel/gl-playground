#include "stdafx.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "Settings.h"
#include "World.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"

#ifndef STGAME_GAME
#define STGAME_GAME


class Game
{

private:

	Settings _settings;
	World _world;
	Camera _camera;
	Renderer _renderer;
	Player _player;

	SDL_Window* _window;
	SDL_GLContext _glcontext;
	SDL_Event _event;
	Mix_Music* _music;

	bool _sdl_initialized;
	bool _running;

	void _handle_events();
	void _cleanup();

public:

	Game();
	~Game();

	void run();

};


#endif