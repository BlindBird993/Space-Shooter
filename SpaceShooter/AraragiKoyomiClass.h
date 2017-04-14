#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SceneObject.hpp"
#include <iostream>
class AraragiKoyomiClass : public SceneObject
{
public:
	AraragiKoyomiClass();
	~AraragiKoyomiClass();
	int list_id;

protected:
	 void privateInit();
	 void privateRender();
	 void privateUpdate();

	 GLuint texture_;
	 //int width, height;
};

