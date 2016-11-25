#include "stdafx.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_mixer.h"


Game::Game()
{
	_running = false;
	_sdl_initialized = false;
	_window = NULL;
	_glcontext = NULL;
}


Game::~Game()
{

	_cleanup();
	//system("pause");

}


void Game::_cleanup()
{

	if (_music)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(_music);
		Mix_CloseAudio();
	}

	if (_glcontext)
	{
		SDL_GL_DeleteContext(_glcontext);
	}

	if (_window)
	{
		SDL_DestroyWindow(_window);
	}

	if (_sdl_initialized)
	{
		SDL_Quit();
	}

}


void Game::run()
{

	// bla
	_camera.viewport_w = _settings.g_width;
	_camera.viewport_h = _settings.g_height;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		return;
	}
	_sdl_initialized = true;

	_window = SDL_CreateWindow(
		"Hello World!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_settings.g_fullscreen ? _settings.g_fs_width : _settings.g_width,
		_settings.g_fullscreen ? _settings.g_fs_width : _settings.g_height,
		_settings.g_fullscreen ? SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL
		);
	if (!_window)
	{
		printf("SDL_CreateWindow: %s\n", SDL_GetError());
		return;
	}

	_glcontext = SDL_GL_CreateContext(_window);
	if (!_glcontext)
	{
		printf("SDL_GL_CreateContext: %s\n", SDL_GetError());
		return;
	}
	SDL_GL_SetSwapInterval(0);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("glewInit error\n");
		return;
	}

	_renderer.initialize(&_world, &_camera);

	// audio
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) != 0)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		return;
	}
	_music = Mix_LoadMUS("D:/Dev/assets/dark_avenger.ogg");
	if (!_music)
	{
		printf("Mix_LoadMUS: %s\n", Mix_GetError());
		return;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME/100 * _settings.s_music_volume);
	if (Mix_PlayMusic(_music, 0) == -1)
	{
		printf("Unable to play Ogg file: %s\n", Mix_GetError());
		return;
	}

	_running = true;
	while (_running)
	{

		_handle_events();
		_renderer.render(&_world, &_camera);
		SDL_GL_SwapWindow(_window);

	}

	_renderer.cleanup();
	_cleanup();

}


void Game::_handle_events()
{

	if (SDL_PollEvent(&_event))
	{
		switch (_event.type)
		{

		case SDL_QUIT:
			_running = false;
			break;

		case SDL_KEYDOWN:
			//...
			break;

		case SDL_KEYUP:
			//...
			_running = false;
			break;

		}
	}

}

