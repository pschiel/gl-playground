#include "stdafx.h"

#ifndef STGAME_SETTINGS
#define STGAME_SETTINGS

class Settings
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