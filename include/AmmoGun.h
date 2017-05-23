#pragma once
#include <windows.h>
#include <iostream>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ParticlesEngineClass.h"
#include "SceneObject.hpp"
#include "ShaderOne.h"
#include "Skybox.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
class AmmoGun : public SceneObject
{
public:
	AmmoGun();
	~AmmoGun();
	int list_id;

	void drawTorus(double r, double c, int rSeg, int cSeg);
	std::vector< std::vector<float>> getVertexArr();

	glm::vec3 getPos() const;
	glm::vec3 getDS() const;
	float getRadius() const;

	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	float boundaryX;
	float boundaryY;

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();
};