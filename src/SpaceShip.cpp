#define _CRT_SECURE_NO_WARNINGS

#include "SpaceShip.hpp"
#include "SOIL.h"

SpaceShip::SpaceShip()
{

	this->currentWeapon = "MachineGun";
	machinegunBullets = 100;
	laserBullets = 50;
	this->life_ = 100;
	this->armor_ = 50;
	maxX = 15;
	minX = 0;
	maxY = 15;
	minY = 0;
	maxZ = 15;
	minZ = 0;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::shipMoveRight()
{
	if (matrix_[3][0] <= 50.f)
		matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}

void SpaceShip::shipMoveLeft()
{
	if (matrix_[3][0] >= -50.f)
		matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}

//void SpaceShip::shipMoveBackward()
//{
//	if (matrix_[3][2] <= -10.f)
//		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
//}

//void SpaceShip::shipMoveForward()
//{
//	if (matrix_[3][2] >= -50.f)
//		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
//}

//get position
glm::vec3 SpaceShip::getPos() const
{
	return glm::vec3(matrix_[3][0], matrix_[3][1], matrix_[3][2]);
}


float SpaceShip::getRadius() const
{
	auto eps = 1e-5;

	float centX1, centY1, centZ1, radius;

	if ((minX + maxX) / 2 < eps) centX1 = 0;
	else centX1 = (minX + maxX) / 2;

	if ((minY + maxY) / 2 < eps) centY1 = 0;
	else centY1 = (minY + maxY) / 2;

	float distanceX1 = 0.0f;
	float xVarMax1 = std::abs(maxX) - std::abs(centX1);
	float xVarMin1 = std::abs(minX) - std::abs(centX1);

	if (xVarMax1 > xVarMin1) distanceX1 = xVarMax1;
	else distanceX1 = xVarMin1;

	float distanceY1 = 0.0f;
	float yVarMax1 = std::abs(maxY) - std::abs(centY1);
	float yVarMin1 = std::abs(minY) - std::abs(centY1);

	if (yVarMax1 > yVarMin1) distanceY1 = yVarMax1;
	else distanceY1 = yVarMin1;

	if (distanceX1 > distanceY1) radius = distanceX1;
	else radius = distanceY1;

	return radius;

}

void SpaceShip::setWeapon(std::string weapon)
{
	this->currentWeapon = weapon;
}

std::string SpaceShip::getWeapon() const
{
	return this->currentWeapon;
}

void SpaceShip::changeWeapon(std::string weapon)
{
	this->setWeapon(weapon);
}


void SpaceShip::reload()
{
	if (currentWeapon == "MachineGun" && machinegunBullets < 1) machinegunBullets += 100;
	if (currentWeapon == "Laser" && laserBullets < 1) laserBullets += 100;

}

int SpaceShip::getLaserAmount()
{
	return this->laserBullets;
}

int SpaceShip::getMachineGunAmount()
{
	return this->machinegunBullets;
}

bool SpaceShip::shoot()
{
	if (currentWeapon == "MachineGun" && machinegunBullets > 0)
	{
		machinegunBullets -= 1;
		return true;
	}

	if (currentWeapon == "Laser"  && laserBullets > 0)
	{
		laserBullets -= 1;
		return true;
	}

	return false;
}

int SpaceShip::getLife()
{
	return this->life_;
}

int SpaceShip::getArmor()
{
	return this->armor_;
}

void SpaceShip::setLife(float damage)
{
	this->life_ -= damage;
}

void SpaceShip::setArmor(float damage)
{
	this->armor_ -= damage;
}



void SpaceShip::privateInit()
{

	//texture initiation
	int width, height;

	unsigned char* img = SOIL_load_image("../textures/particle.png", &width, &height, 0, SOIL_LOAD_RGB);//color

	glGenTextures(1, &particleTexture_);
	glBindTexture(GL_TEXTURE_2D, particleTexture_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;

	if (particleTexture_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());
	}
	else {
		std::cout << "Texture loaded: " << "size " << sizeof(img) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

		SOIL_free_image_data(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	particles_ptr.reset(new ParticlesEngineClass(particleTexture_,this->matrix_));
	this->addSubObject(particles_ptr);

	spaceshipShader_.initShaders("../Shaders/red");
	spaceshipShader_.enable();

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f));
	spaceshipShader_.disable();

	vertexArray_ = {
		glm::vec3(0.0f, 0.0f, -11.25f), glm::vec3(-7.5f, 0.0f, 2.5f), glm::vec3(-13.0f, 0.0f, -8.0f),
		glm::vec3(-13.0f, 2.5f, 10.0f), glm::vec3(-7.5f, 0.0f, 6.25f), glm::vec3(0.0f, 2.5f, 10.0f),
		glm::vec3(7.5f, 0.0f, 6.25f), glm::vec3(13.0f, 2.5f, 10.0f), glm::vec3(13.0f, 0.0f, -8.0f),
		glm::vec3(7.5f, 0.0f, 2.5f)
	};

	indexArray_ = { 9, 0, 1,	1, 2, 3,	4, 1, 3,	5, 1, 4,	5, 9, 1,  6, 9, 5,	7, 9, 6,	7, 8, 9 };
}

void SpaceShip::privateRender()
{

	spaceshipShader_.enable();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	glDrawElements(GL_TRIANGLES, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);
	glDisableClientState(GL_VERTEX_ARRAY);


	spaceshipShader_.disable();



}

void SpaceShip::privateUpdate()
{

}

