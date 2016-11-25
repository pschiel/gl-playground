#define GAMELIB_EXPORTS
#include "stdafx.h"
#include "Settings.h"


Settings::Settings()
{
	g_width = 1280;
	g_height = 800;
	g_fs_width = 1920;
	g_fs_height = 1200;
	g_fullscreen = false;

	s_music_volume = 0;
}


Settings::~Settings()
{
}
