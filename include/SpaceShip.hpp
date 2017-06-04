#pragma once
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ParticlesEngineClass.h"
#include "SceneObject.hpp"
#include "Bullets.h"
#include "ShaderOne.h"
#include "Skybox.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class SpaceShip : public SceneObject
{
public:
	SpaceShip();
	~SpaceShip();
	int list_id;

	void shipMoveRight();
	void shipMoveLeft();
	void shipMoveBackward();
	void shipMoveForward();

	GLuint particleTexture_;
	std::shared_ptr<ParticlesEngineClass> particles_ptr;

	glm::vec3 getPos() const;
	float getRadius() const;

	GLfloat m[16];

	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	float boundaryX;
	float boundaryY;

	void setWeapon(std::string weapon);
	std::string getWeapon() const;
	void changeWeapon(std::string weapon);
	void reload();
	int getLaserAmount();
	int getMachineGunAmount();
	bool shoot();

	int getLife();
	int getArmor();

	void setLife(float damage);
	void setArmor(float damage);

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	float speed_;
	int life_;
	int armor_;

	Shader spaceshipShader_;
	GLuint textureName_;
	GLuint cubeTextures_;

	std::vector<glm::vec3> vertexArray_;
	std::vector<unsigned int> indexArray_; //vertex array

	// Weapons
	std::string currentWeapon;
	int laserBullets;
	int machinegunBullets;

};

