#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "BMPLoader.h"
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Enemy : public SceneObject
{
public:
	Enemy();
	~Enemy();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	float speed_;
	float life_;
	float armor_;
	
	bool checkFlag = true;
	float max_z = 50.0;
	float min_z = 0.0;

	float max_y = 30.0;
	float min_y = 0.0;

	double z_coord = 0.0;
	double y_coord = 0.0;

    BMPClass textureClass_;
	GLuint textureName_;



};

#pragma once
