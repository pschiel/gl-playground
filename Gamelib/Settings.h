#include "stdafx.h"

#ifndef GAMELIB_SETTINGS
#define GAMELIB_SETTINGS

class GAMELIB_API Settings
{

private:


public:

	int g_width;
	int g_height;
	int g_fs_width;
	int g_fs_height;
	bool g_fullscreen;
	
	int s_music_volume;

	Settings();
	~Settings();

};

#endif