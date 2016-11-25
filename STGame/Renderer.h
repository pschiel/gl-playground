#include "stdafx.h"
#include "gl/glew.h"
#include "World.h"
#include "Camera.h"

#ifndef STGAME_RENDERER
#define STGAME_RENDERER

class Renderer
{

private:

	GLuint VertexArrayID;
	GLuint vertexbuffer;

public:

	Renderer();
	~Renderer();

	void initialize(World* world, Camera* camera);
	void cleanup();
	void resize(Camera* camera);
	void render(World* world, Camera* camera);

};

#endif