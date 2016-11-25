#include "stdafx.h"
#include "gl/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "Camera.h"
#include <fstream>
#include <vector>
#include "SDL_ttf.h"
#include "SDL_image.h"


Renderer::Renderer()
{

	vao = NULL;
	vao2 = NULL;
	buffer = NULL;
	buffer2 = NULL;
	font = NULL;
	tex = NULL;

}


Renderer::~Renderer()
{

	cleanup();

}


void Renderer::cleanup()
{

	if (tex)
	{
		glDeleteTextures(1, &tex);
		tex = NULL;
	}

	if (buffer)
	{
		glDeleteBuffers(1, &buffer);
		buffer = NULL;
	}
	if (buffer2)
	{
		glDeleteBuffers(1, &buffer2);
		buffer = NULL;
	}

	if (program)
	{
		glDeleteProgram(program);
		program = NULL;
	}

	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = NULL;
	}
	if (vao2)
	{
		glDeleteVertexArrays(1, &vao2);
		vao = NULL;
	}

}


void Renderer::render(World* world, Camera* camera)
{

	glm::vec3 pos = glm::vec3(camera->x, camera->y, camera->z);
	glm::vec3 dir = glm::vec3(cos(camera->rot_x) * sin(camera->rot_y), sin(camera->rot_x), cos(camera->rot_x) * cos(camera->rot_y));
	glm::vec3 right = glm::vec3(sin(camera->rot_y - 3.14f/2.0f), 0, cos(camera->rot_y - 3.14f/2.0f));
	glm::vec3 up = glm::cross(right, dir);

	glm::mat4 projection_matrix = glm::perspective(camera->fov, (float)camera->viewport_w / (float)camera->viewport_h, 0.1f, 200.0f);
	glm::mat4 view_matrix = glm::lookAt(pos, pos + dir, up);
	glm::mat4 model_matrix = glm::mat4(1.0);
	glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

	glViewport(camera->viewport_x, camera->viewport_y, camera->viewport_w, camera->viewport_h);
	glScissor(camera->viewport_x, camera->viewport_y, camera->viewport_w, camera->viewport_h);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(vao);
	glUniform1i(test_location, 4);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(vao2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(tex_location, 0);
	glUniform1i(test_location, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6 * 100 * 100);
	glBindVertexArray(0);

	glUniform1i(test_location, 1);
	glBegin(GL_LINES);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glEnd();
	glUniform1i(test_location, 2);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -1000.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glEnd();
	glUniform1i(test_location, 3);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glEnd();

};


void Renderer::initialize(World* world, Camera* camera)
{
	
	static const GLfloat buffer_data[] = {
		0.0f,  3.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};

	static GLfloat buffer_data2[6 * 3 * 100 * 100];
	static GLfloat uvbuffer_data2[6 * 2 * 100 * 100];

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			buffer_data2[6*3*100*y + 6*3*x + 0] = (float)x;
			buffer_data2[6*3*100*y + 6*3*x + 1] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 2] = (float)(y+1);

			uvbuffer_data2[6*2*100*y + 6*2*x + 0] = 0.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 1] = 1.0f;
		
			buffer_data2[6*3*100*y + 6*3*x + 3] = (float)(x+1);
			buffer_data2[6*3*100*y + 6*3*x + 4] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 5] = (float)y;

			uvbuffer_data2[6*2*100*y + 6*2*x + 2] = 1.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 3] = 0.0f;		

			buffer_data2[6*3*100*y + 6*3*x + 6] = (float)x;
			buffer_data2[6*3*100*y + 6*3*x + 7] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 8] = (float)y;

			uvbuffer_data2[6*2*100*y + 6*2*x + 4] = 0.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 5] = 0.0f;		

			buffer_data2[6*3*100*y + 6*3*x + 9] = (float)x;
			buffer_data2[6*3*100*y + 6*3*x + 10] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 11] = (float)(y+1);
		
			uvbuffer_data2[6*2*100*y + 6*2*x + 6] = 0.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 7] = 1.0f;		

			buffer_data2[6*3*100*y + 6*3*x + 12] = (float)(x+1);
			buffer_data2[6*3*100*y + 6*3*x + 13] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 14] = (float)(y+1);

			uvbuffer_data2[6*2*100*y + 6*2*x + 8] = 1.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 9] = 1.0f;		

			buffer_data2[6*3*100*y + 6*3*x + 15] = (float)(x+1);
			buffer_data2[6*3*100*y + 6*3*x + 16] = 0.0f;
			buffer_data2[6*3*100*y + 6*3*x + 17] = (float)y;

			uvbuffer_data2[6*2*100*y + 6*2*x + 10] = 1.0f;
			uvbuffer_data2[6*2*100*y + 6*2*x + 11] = 0.0f;		
		}
	}

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glGenBuffers(1, &buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data2), buffer_data2, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(2, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvbuffer_data2), uvbuffer_data2, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	SDL_Surface *surface = IMG_Load("D:\\Dev\\assets\\grass.bmp");
	if (!surface)
	{
        printf("IMG_Load: %s\n", SDL_GetError());
		return;
    }
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);

	program = load_shaders("C:\\Users\\ops\\Documents\\Visual Studio 2012\\Projects\\Game\\Game1\\shaders\\testshader.vs","C:\\Users\\ops\\Documents\\Visual Studio 2012\\Projects\\Game\\Game1\\shaders\\testshader.fs");
	mvp_location = glGetUniformLocation(program, "mvp");


	test_location = glGetUniformLocation(program, "test");
	tex_location = glGetUniformLocation(program, "tex");
	//if (TTF_Init() < 0)
	//{
	//	printf("TTF_Init: error\n");
	//	return;
	//}

	//font = TTF_OpenFont("C:\\Windows\\fonts\\arial.ttf", 9);


};


GLuint Renderer::load_shaders(const char* vs_filename, const char* fs_filename)
{

	std::ifstream ifs_vs(vs_filename);
	std::string vs((std::istreambuf_iterator<char>(ifs_vs)), std::istreambuf_iterator<char>());

	std::ifstream ifs_fs(fs_filename);
	std::string fs((std::istreambuf_iterator<char>(ifs_fs)), std::istreambuf_iterator<char>());

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int length;

	const char* vs_source = vs.c_str();
	glShaderSource(vertex_shader, 1, &vs_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 1)
	{
		std::vector<char> VertexShaderErrorMessage(length + 1);
		glGetShaderInfoLog(vertex_shader, length, NULL, &VertexShaderErrorMessage[0]);
		printf("glCompileShader: %s: %s\n", vs_filename, &VertexShaderErrorMessage[0]);
	}

	char const* fs_source = fs.c_str();
	glShaderSource(fragment_shader, 1, &fs_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 1)
	{
		std::vector<char> message(length + 1);
		glGetShaderInfoLog(fragment_shader, length, NULL, &message[0]);
		printf("glCompileShader: %s: %s\n", fs_filename, &message[0]);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 1)
	{
		std::vector<char> message(length + 1);
		glGetProgramInfoLog(program, length, NULL, &message[0]);
		printf("glLinkProgram: %s\n", &message[0]);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;

}