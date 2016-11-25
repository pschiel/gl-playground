#include "stdafx.h"
#include "gl/glew.h"
#include "Renderer.h"


Renderer::Renderer()
{

	VertexArrayID = NULL;
	vertexbuffer = NULL;

}


Renderer::~Renderer()
{

	cleanup();

}


void Renderer::cleanup()
{

	if (vertexbuffer)
	{
		glDeleteBuffers(1, &vertexbuffer);
		vertexbuffer = NULL;
	}

	if (VertexArrayID)
	{
		glDeleteVertexArrays(1, &VertexArrayID);
		VertexArrayID = NULL;
	}

}


void Renderer::render(World* world, Camera* camera)
{

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
 
	glDrawArrays(GL_TRIANGLES, 0, 3);
 
	glDisableVertexAttribArray(0);

};


void Renderer::initialize(World* world, Camera* camera)
{

	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

};



void Renderer::resize(Camera* camera)
{
}