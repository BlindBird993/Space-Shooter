
#include "SpaceShip.hpp"
#include "SOIL.h"

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::privateInit()
{
	/*
	const char *texturePath = "../textures/colormap.bmp";
	BMPLoad(texturePath, textureClass_);
	glGenTextures(1, &textureName_);
	glBindTexture(GL_TEXTURE_2D, textureName_);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureClass_.width, textureClass_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureClass_.bytes);*/

	particles_ptr.reset(new ParticlesEngineClass());
	this->addSubObject(particles_ptr);

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f)); 
}

void SpaceShip::privateRender()
{
//glEnable(GL_TEXTURE_2D);
  
glColor3f(1.0f, 1.0f, 1.0f);
  float size = 5.0f;
  glBegin(GL_QUADS);
    // Near Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);
  glEnd();
  //render texture

  //glBindTexture(GL_TEXTURE_2D, textureName_);
  
  glBegin(GL_QUADS);

  glTexCoord2f(0, 0);
  glVertex3f(0, 0, -2);

  glTexCoord2f(1, 0);
  glVertex3f(1, 0, -2);

  glTexCoord2f(1, 1);
  glVertex3f(1, 1, -2);

  glTexCoord2f(0,1);
  glVertex3f(0,1,-2);

  glEnd();

  //glDisable(GL_TEXTURE_2D);

}

void SpaceShip::privateUpdate()
{

}

