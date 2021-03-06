#pragma once

#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "ShaderOne.h"
#include "Camera.hpp"
#include "SOIL.h"

#include "glm/glm.hpp"



static class Skybox : public SceneObject
{
public:
	Skybox(std::shared_ptr<Camera> camera);
	~Skybox();
	GLuint getTextures();


protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

	void loadCubemap();
	void drawCube();

private:

	int list_id;



	Shader shader_;

	GLuint cubeVAO, cubeVBO;
	GLuint skyboxVAO, skyboxVBO;

	std::shared_ptr<Camera> cam_;
	GLuint cubeTextures_;

};