#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BMPLoader.h"
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include <iostream>

class BattleField : public SceneObject
{
	public:
		BattleField();
		~BattleField();

  protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:

	BMPClass textureClass_;
	GLuint textureName_;
	//int width, height;

    std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2 > textureArray_;
										   
										   // normal array.
    // texture coord array
};
