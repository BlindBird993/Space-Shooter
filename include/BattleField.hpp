#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "ShaderOne.h"
#include "Skybox.h"

class BattleField : public SceneObject
{
public:
	BattleField(int width_, int height_, int depth_);
	BattleField();
	~BattleField();

	int getBattleWidth();
	int getBattleDepth();
	int getBattleHeight();
	void setZpos(float zpos);

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:

	//BMPClass textureClass_;
	GLuint textureName_;//texture
	GLuint secondTextureName_;//hightmap

	GLuint lightTextureName_;//light
	GLuint normalTextureName_;//normal

	GLuint skybox_;

	Shader vertexShader_;
	Shader fragShader_;

	Shader shader_;


	int width_, height_, depth_;

	std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2 > textureArray_;

	// normal array.
// texture coord array
};

