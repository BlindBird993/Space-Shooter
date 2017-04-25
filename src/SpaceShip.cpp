
#include "SpaceShip.hpp"
#include "SOIL.h"

SpaceShip::SpaceShip()
{
	setWeapon(new MachineGun(100));
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::shipMoveRight()
{
	matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}

void SpaceShip::shipMoveLeft()
{
	matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}

void SpaceShip::shipMoveUp()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 5.0f, 0.0f));
}

void SpaceShip::shipMoveDown()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -5.0f, 0.0f));
}

void SpaceShip::shipMoveBackward()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}

void SpaceShip::shipMoveForward()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
}

std::vector<std::vector<float>> SpaceShip::getVertexArr()
{
	return vertexArray_;
}



void SpaceShip::setWeapon(Weapon * weapon_)
{
	this->weapon = weapon_;
}

Weapon * SpaceShip::getWeapon() const
{
	return this->weapon;
}

void SpaceShip::changeWeapon(Weapon * weapon)
{
	delete this->weapon;
	this->weapon = weapon;
}

void SpaceShip::reload()
{
	this->weapon->addAmmo();
}

void SpaceShip::privateInit()
{
	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);//begin new list

	glColor3f(0.0f, 0.0f, 1.0f);
	float size = 5.0f;

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size); vertexArray_.push_back(std::vector<float>{ -size, -size, size});
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size); vertexArray_.push_back(std::vector<float>{size, -size, size});
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size); vertexArray_.push_back(std::vector<float>{ size, size, size});
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size); vertexArray_.push_back(std::vector<float>{-size, size, size});
	glEnd();

	glEndList();//end new list

	particles_ptr.reset(new ParticlesEngineClass());
	this->addSubObject(particles_ptr);
	
	spaceshipShader_.initShaders("../Shaders/red");

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f)); 
}

void SpaceShip::privateRender()
{
//glEnable(GL_TEXTURE_2D);
	spaceshipShader_.enable();
	glCallList(list_id);
	spaceshipShader_.disable();
  //render texture

  //glBindTexture(GL_TEXTURE_2D, textureName_);
  
  //glBegin(GL_QUADS);

  //glTexCoord2f(0, 0);
  //glVertex3f(0, 0, -2);

  //glTexCoord2f(1, 0);
  //glVertex3f(1, 0, -2);

  //glTexCoord2f(1, 1);
  //glVertex3f(1, 1, -2);

  //glTexCoord2f(0,1);
  //glVertex3f(0,1,-2);

  //glEnd();

  //glDisable(GL_TEXTURE_2D);

}

void SpaceShip::privateUpdate()
{

}

void SpaceShip::getSpaceShipPosition()
{
}

