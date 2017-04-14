#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BMPLoader.h"
//#include "SpaceShooter\ParticlesClass.h"
#include "SpaceShooter\ParticlesEngineClass.h"
#include "SceneObject.hpp"

class SpaceShip : public SceneObject
{
	public:
		SpaceShip();
		~SpaceShip();

  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
	  float speed_;
    float life_;
    float armor_;
	
	BMPClass textureClass_;
	GLuint textureName_;

	//bool	active = TRUE;				// Window Active Flag Set To TRUE By Default
	//bool	fullscreen = TRUE;			// Fullscreen Flag Set To Fullscreen Mode By Default
	//bool	rainbow = true;				// Rainbow Mode?
	//bool	sp;							// Spacebar Pressed?
	//bool	rp;							// Enter Key Pressed?

	//float	slowdown = 2.0f;				// Slow Down Particles
	//float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	//float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
	//float	zoom = -40.0f;				// Used To Zoom Out
	//GLuint	loop;						// Misc Loop Variable
	//GLuint	col;						// Current Color Selection
	//GLuint	delay = 0;						// Rainbow Effect Delay
	//GLuint	texture[1];					// Storage For Our Particle Texture

	//static const int MAX_PARTICLES = 1000;


	//ParticlesClass particlesArray_[MAX_PARTICLES];
	//    GLfloat colors[12][3] = {
	//	{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
	//	{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
	//	{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
	//};
	std::shared_ptr<ParticlesEngineClass> particles_ptr;
};

