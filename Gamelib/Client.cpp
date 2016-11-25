#define GAMELIB_EXPORTS
#include "stdafx.h"
#include "Client.h"
#include "Renderer.h"
#include "SDL_mixer.h"


Client::Client()
{
	_window = NULL;
	_glcontext = NULL;
	_state = "uninitialized";
	_input_thread = NULL;
	_render_thread = NULL;
}


Client::~Client()
{
	if (_state == "started")
	{
		stop();
	}
}


void Client::start()
{
	if (_state == "started")
	{
		printf("Already started\n");
		return;
	}
	_state = "starting";
	printf("starting\n");
	_input_thread = new boost::thread(boost::bind(&Client::input_thread, this));
	while (_state != "started" && _state != "stopped");
}


void Client::stop()
{
	if (_state != "started")
	{
		printf("Not started\n");
		return;
	}
	_state = "stopping";
	printf("stopping\n");
	_input_thread->join();
	delete _input_thread;
	_input_thread = NULL;
}


void Client::restart()
{
	stop();
	start();
}


std::string Client::getState()
{
	return _state;
}


void Client::input_thread()
{
	SDL_Event event;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		return;
	}
	_window = SDL_CreateWindow("Hello World!", 100, 100, settings.g_width, settings.g_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!_window)
	{
		printf("SDL_CreateWindow: %s\n", SDL_GetError());
		return;
	}

	bool relative_mousemode = true;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	 
    SDL_JoystickEventState(SDL_ENABLE);
	SDL_Joystick* joystick = SDL_JoystickOpen(0);

	// audio
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) != 0)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		return;
	}
	//Mix_Music* music = Mix_LoadMUS("D:\\Dev\\assets\\dark_avenger.ogg");
	//if (!music)
	//{
	//	printf("Mix_LoadMUS: %s\n", Mix_GetError());
	//	return;
	//}
	//Mix_VolumeMusic(MIX_MAX_VOLUME/100 * settings.s_music_volume);
	//if (Mix_PlayMusic(music, 0) == -1)
	//{
	//	printf("Unable to play Ogg file: %s\n", Mix_GetError());
	//	return;
	//}

	_state = "started";
	printf("started\n");
	_render_thread = new boost::thread(boost::bind(&Client::render_thread, this));

	while (_state == "started")
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{

			case SDL_QUIT:
				_state = "stopping";
				printf("stopping\n");
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_q:
					_state = "stopping";
					printf("stopping\n");
					break;
				case SDLK_ESCAPE:
					relative_mousemode = !relative_mousemode;
					SDL_SetRelativeMouseMode(relative_mousemode ? SDL_TRUE : SDL_FALSE);
					printf("mouse mode %s\n", relative_mousemode ? "rel" : "abs");
					break;
				case SDLK_h:
					camera.lookat(0.0f, 0.0f, 0.0f);
					break;
				}
				break;

			case SDL_MOUSEMOTION:
				if (relative_mousemode)
				{
					//printf("mouse rel x %d y %d\n", event.motion.xrel, event.motion.yrel);
				}
				else 
				{
					//printf("mouse abs x %d y %d\n", event.motion.x, event.motion.y);
				}
				break;

			case SDL_JOYAXISMOTION:
				printf("axis %d value %d\n", (int)event.jaxis.axis, event.jaxis.value);
				if (event.jaxis.axis == 0)
				{
					camera.rot_y = 0.785f + (float)(-event.jaxis.value / 30000.0);
				}
				if (event.jaxis.axis == 1)
				{
					camera.y = 2.0f - (float)(event.jaxis.value / 10000.0);
				}
				if (event.jaxis.axis == 5)
				{
					camera.z = -5.0f + (float)(event.jaxis.value / 6000.0);
					camera.x = camera.z;
				}
				break;

			case SDL_JOYBUTTONDOWN:
				printf("joybutton %d\n", (int)event.jbutton.button);
				break;

			}

		}
	}

	_render_thread->join();
	delete _render_thread;

	Mix_HaltMusic();
	//Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_JoystickClose(joystick);
	SDL_DestroyWindow(_window);
	SDL_Quit();

	_state = "stopped";
	printf("stopped\n");
}


void Client::render_thread() 
{

	Renderer renderer;

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
		printf("glewInit: error\n");
		return;
	}

	renderer.initialize(&world, &camera);

	Camera rear_cam;
	rear_cam.viewport_x = 20;
	rear_cam.viewport_y = 20;
	rear_cam.viewport_w = 200;
	rear_cam.viewport_h = 200;

	while (_state == "started")
	{
		rear_cam.x = camera.x;
		rear_cam.y = camera.y;
		rear_cam.z = camera.z;
		rear_cam.lookat(0.0, 0.0, 0.0);
		renderer.render(&world, &camera);
		renderer.render(&world, &rear_cam);
		SDL_GL_SwapWindow(_window);
	}

	renderer.cleanup();
	SDL_GL_DeleteContext(_glcontext);

}


void Client::sleep(int seconds)
{
	SDL_Delay(seconds * 1000);
}

