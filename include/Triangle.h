#pragma once


#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

class Triangle:public SceneObject
{
public:
	Triangle();
	~Triangle();


protected:
	void privateInit();
	void privateRender();
	void privateUpdate();





};

