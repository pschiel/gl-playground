#pragma once
#pragma warning(disable: 4251)

#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport)
#else
#define GAMELIB_API __declspec(dllimport)
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
