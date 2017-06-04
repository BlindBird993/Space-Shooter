#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "ParticlesClass.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SOIL.h"

class ParticlesEngineClass : public SceneObject
{
public:
	ParticlesEngineClass(GLuint textureName, glm::mat4 matrix);
	~ParticlesEngineClass();
	GLuint textureName_;
	glm::mat4 matrix;


	bool	active = TRUE;				
	bool	fullscreen = TRUE;			
	bool	rainbow = true;				
	bool	sp;							
	bool	rp;							

	float	slowdown = 2.0f;				
	float	xspeed;						
	float	yspeed;						
	float	zoom = -40.0f;				
	float	partlife =100.0f;
	GLuint	loop;						
	GLuint	col;						
	GLuint	delay = 0;						
	GLuint	texture[1];					

	static const int MAX_PARTICLES = 1000;
	ParticlesClass particlesArray_[MAX_PARTICLES];

	int dir_;

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

