#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "BMPLoader.h"
#include "SceneObject.hpp"
#include "SpaceShooter\ParticlesClass.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ParticlesEngineClass : public SceneObject
{
public:
	ParticlesEngineClass();
	~ParticlesEngineClass();
/**
	//const GLfloat vertex_buffer_data[4][3] = {
	//	{-0.5f, -0.5f, 0.0f},
	//	{0.5f, -0.5f, 0.0f},
	//	{-0.5f, 0.5f, 0.0f},
	//	{0.5f, 0.5f, 0.0f},
	//};
	// GLuint billboard_vertex_buffer;
	// glGenBuffers(1, &billboard_vertex_buffer);
	// glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	**/
	BMPClass textureClass_;
	GLuint textureName_;	
	

	bool	active = TRUE;				// Window Active Flag Set To TRUE By Default
	bool	fullscreen = TRUE;			// Fullscreen Flag Set To Fullscreen Mode By Default
	bool	rainbow = true;				// Rainbow Mode?
	bool	sp;							// Spacebar Pressed?
	bool	rp;							// Enter Key Pressed?

	float	slowdown = 2.0f;				// Slow Down Particles
	float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
	float	zoom = -40.0f;				// Used To Zoom Out
	GLuint	loop;						// Misc Loop Variable
	GLuint	col;						// Current Color Selection
	GLuint	delay = 0;						// Rainbow Effect Delay
	GLuint	texture[1];					// Storage For Our Particle Texture

	static const int MAX_PARTICLES = 1000;


	ParticlesClass particlesArray_[MAX_PARTICLES];
	GLfloat colors[12][3] = {
		{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
		{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
		{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
	};

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

};

