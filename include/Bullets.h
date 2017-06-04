#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Weapon.h"
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Bullets : public SceneObject
{
public:
	Bullets(std::string type, glm::mat4 position, bool friendly, int depth);
	~Bullets();
	glm::vec3 getPosition();

	int life_;
	int bullets;
	void createBullets();

	glm::vec3 getPos() const;
	float getRadius() const;
	bool collFlag = false;
	int damage_;


protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	std::string type_;
	glm::vec3 position_;
	bool friendly_;
	int depth_;
	float increment = 0.0f;


	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	std::vector< std::vector<float>> vertexArray_; //vertex array
};

