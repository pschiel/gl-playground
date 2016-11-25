#include "stdafx.h"
#include "gl/glew.h"
#include "World.h"
#include "Camera.h"
#include "SDL_ttf.h"

#ifndef GAMELIB_RENDERER
#define GAMELIB_RENDERER

class GAMELIB_API Renderer
{

private:

	GLuint program;
	GLuint vao, vao2;
	GLuint buffer, buffer2, uvbuffer2;
	GLuint mvp_location;
	GLuint tex_location;
	GLuint test_location;
	GLuint tex;
	TTF_Font *font;

public:

	Renderer();
	~Renderer();

	void initialize(World *world, Camera *camera);
	void cleanup();
	void render(World *world, Camera *camera);
	GLuint load_shaders(const char *vs_filename, const char *fs_filename);

};

#endif