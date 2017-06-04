//#pragma once
//#include <windows.h>
//#include <iostream>
//#include <GL/glew.h> 
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "SceneObject.hpp"
//#include "ShaderOne.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//class AmmoLazer : public SceneObject
//{
//public:
//	AmmoLazer(float startPos, float xPos);
//	~AmmoLazer();
//	int list_id;
//
//
//	void drawCube();
//	glm::vec3 getPos() const;
//	glm::vec3 getDS() const;
//	float getRadius() const;
//
//	float startPos_;
//	float xPos_;
//	bool isActive_ = true;
//
//	bool testFlag = false;
//	GLfloat     rtri = 0.0f;                       // Angle For The Triangle ( NEW )
//	GLfloat     rquad = 0.0f;                      // Angle For The Quad     ( NEW )
//
//	float maxX;
//	float minX;
//	float maxY;
//	float minY;
//	float maxZ;
//	float minZ;
//
//	Shader ammoShader_;
//
//protected:
//	void privateInit();
//	void privateRender();
//	void privateUpdate();
//};