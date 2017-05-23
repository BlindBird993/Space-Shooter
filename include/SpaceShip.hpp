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
//#include "Weapon.h"
#include "MachineGun.h"
#include "Lazer.h"
#include "Bullets.h"
#include "ShaderOne.h"
#include "Skybox.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class SpaceShip : public SceneObject
{
	public:
		SpaceShip(std::shared_ptr<Skybox> skybox_);
		~SpaceShip();
		int list_id;

		void shipMoveRight();
		void shipMoveLeft();
		void shipMoveUp();
		void shipMoveDown();
		void shipMoveBackward();
		void shipMoveForward();

		void drawCube();

		void drawTorus(double r, double c, int rSeg, int cSeg);
		std::vector< std::vector<float>> getVertexArr();

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
		bool loadModel(const char * path,
			std::vector < glm::vec3 > & out_vertices,
			std::vector < glm::vec2 > & out_uvs,
			std::vector < glm::vec3 > & out_normals);
		void load(const char* filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);

  protected:
    void privateInit();
	void privateRender();
	void privateUpdate();

	private:
	float speed_;
    float life_;
    float armor_;
	
	Shader spaceshipShader_;
	GLuint textureName_;
	GLuint cubeTextures_;
	GLuint particleTexture_;

	std::shared_ptr<ParticlesEngineClass> particles_ptr;


	bool testFlag = false;
	GLfloat     rtri = 0.0f;                       // Angle For The Triangle ( NEW )
	GLfloat     rquad = 0.0f;                      // Angle For The Quad     ( NEW )

	std::vector< std::vector<float>> vertexArray_; //vertex array

	// Weapons
	std::string currentWeapon;
	int laserBullets;
	int machinegunBullets;

	std::shared_ptr<Skybox> skybox_;



};

