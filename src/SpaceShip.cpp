#define _CRT_SECURE_NO_WARNINGS
#include <assimp\cimport.h>
#include <assimp\postprocess.h>

//#include "assimp/Importer.hpp" //OO version Header! 
//#include "assimp/postprocess.h" 
//#include "assimp/scene.h" 
//#include "assimp/DefaultLogger.hpp" 
//#include "assimp/LogStream.hpp"

#include "SpaceShip.hpp"
#include "SOIL.h"

SpaceShip::SpaceShip(std::shared_ptr<Skybox> skybox_)
{
	this->skybox_ = skybox_;
	this->currentWeapon = "MachineGun";
	machinegunBullets = 100;
	laserBullets = 100;
	this->life_ = 200;
	this->armor_ = 100;
	//setWeapon(new MachineGun(100));
	maxX = 5;
	minX = 0;
	maxY = 5;
	minY = 0;
	maxZ = 5;
	minZ = 0;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::shipMoveRight()
{
	if (matrix_[3][0] <= 100.f)
	matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}

void SpaceShip::shipMoveLeft()
{
	if (matrix_[3][0] >= -100.f)
	matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}

void SpaceShip::shipMoveUp()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 5.0f, 0.0f));
}

void SpaceShip::shipMoveDown()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -5.0f, 0.0f));
}

void SpaceShip::shipMoveBackward()
{
	if (matrix_[3][2] <= -10.f)
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}

void SpaceShip::shipMoveForward()
{
	if (matrix_[3][2] >= -7400.f)
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
}

std::vector<std::vector<float>> SpaceShip::getVertexArr()
{
	return vertexArray_;
}
//get position
glm::vec3 SpaceShip::getPos() const
{
	return glm::vec3(matrix_[3][0], matrix_[3][1], matrix_[3][2]);
}


float SpaceShip::getRadius() const
{
	auto eps = 1e-5;

	float centX1, centY1, centZ1, radius;

	if ((minX + maxX) / 2 < eps) centX1 = 0;
	else centX1 = (minX + maxX) / 2;

	if ((minY + maxY) / 2 < eps) centY1 = 0;
	else centY1 = (minY + maxY) / 2;
	/******************************************************************************************/
	//if ((zMin + zMax) / 2 < eps) centY = 0;
	//else centZ = (zMin + zMax) / 2;

	float distanceX1 = 0.0f;
	float xVarMax1 = std::abs(maxX) - std::abs(centX1);
	float xVarMin1 = std::abs(minX) - std::abs(centX1);

	if (xVarMax1 > xVarMin1) distanceX1 = xVarMax1;
	else distanceX1 = xVarMin1;

	float distanceY1 = 0.0f;
	float yVarMax1 = std::abs(maxY) - std::abs(centY1);
	float yVarMin1 = std::abs(minY) - std::abs(centY1);

	if (yVarMax1 > yVarMin1) distanceY1 = yVarMax1;
	else distanceY1 = yVarMin1;

	if (distanceX1 > distanceY1) radius = distanceX1;
	else radius = distanceY1;

	return radius;

}

void SpaceShip::setWeapon(std::string weapon)
{
	this->currentWeapon = weapon;
}

std::string SpaceShip::getWeapon() const
{
	return this->currentWeapon;
}


void SpaceShip::reload()
{
	if (currentWeapon == "MachineGun" && machinegunBullets < 1) machinegunBullets += 100;
	if (currentWeapon == "Lazer" && laserBullets < 1) laserBullets += 100;

}

int SpaceShip::getLaserAmount()
{
	return this->laserBullets;
}

int SpaceShip::getMachineGunAmount()
{
	return this->machinegunBullets;
}

bool SpaceShip::shoot()
{
	if (currentWeapon == "MachineGun" && machinegunBullets > 0)
	{
		machinegunBullets -= 1;
		return true;
	}

	if (currentWeapon == "Laser"  && laserBullets > 0)
	{
		laserBullets -= 1;
		return true;
	}

	return false;
}



void SpaceShip::privateInit()
{

	//model load
	obj.Load("../textures/models/222.obj");
	//const aiScene* spaceShipModel = aiImportFile("../textures/SpaceShip.fbx",aiProcessPreset_TargetRealtime_MaxQuality);
	
	//texture initiation
	int width, height;

	unsigned char* img = SOIL_load_image("../textures/particle.png", &width, &height, 0, SOIL_LOAD_RGB);//color

	glGenTextures(1, &particleTexture_);
	glBindTexture(GL_TEXTURE_2D, particleTexture_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;

	if (particleTexture_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());
	}
	else {
		std::cout << "Texture loaded: " << "size " << sizeof(img) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

		SOIL_free_image_data(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	

	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);//begin new list
	glColor3f(0.0f, 0.0f, 1.0f);
	//float size = 5.0f;
	float angle = 90.0;
	glEndList();//end new list

	particles_ptr.reset(new ParticlesEngineClass(particleTexture_));
	this->addSubObject(particles_ptr);
	
	cubeTextures_ = skybox_->getTextures();



	spaceshipShader_.initShaders("../Shaders/phong");
	spaceshipShader_.enable();

	glUniform3f(glGetUniformLocation(spaceshipShader_.getProg(), "ObjColor"), 1.000f, 0.843f, 0.000f);
	glUniform3f(glGetUniformLocation(spaceshipShader_.getProg(), "LightPosition"), -1.0, -100.0, 3.0);
	//GLint texture1 = glGetUniformLocation(spaceshipShader_.getProg(), "cube_texture");//fragment
	//glUniform1i(texture1, 0);

	//if (cubeTextures_ == NULL) { std::cout << "Fail" << std::endl; }

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f));
	spaceshipShader_.disable();
}

void SpaceShip::privateRender()
{

	spaceshipShader_.enable();

	/*glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cubeTextures_);*/
	
	drawCube();
	//glLoadIdentity();
	//drawShip();

	/*glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);*/


	spaceshipShader_.disable();


	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//drawShip();
	//glutSwapBuffers(); //swap the buffers

}

void SpaceShip::privateUpdate()
{

	//if (testFlag == false)
	//	rtri += 0.5f;
	//else
	//	rtri -= 0.5f;
	//if (rtri == 1000.0f)
	//	testFlag = true;
	//if (rtri == 0.0f)
	//	testFlag = false;


	//from -5 to -inf
	//std::cout << matrix_[3][2] << " " << std::endl;
	//std::cout << matrix_[3][0] <<" "<< matrix_[3][1] << std::endl;

	
}



void SpaceShip::drawShip()
{
	//glPushMatrix();
	//glTranslatef(0, 0, 5);//-40.00, -105);
	//glColor3f(1.0, 0.23, 0.27);
	//glScalef(2, 2, 2);
	////glRotatef(elephantrot, 0, 1, 0);
	//glCallList(elephant);
	//glPopMatrix();
	//elephantrot = elephantrot + 0.6;
	//if (elephantrot>360)elephantrot = elephantrot - 360;
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glColor3f(1.0, 0.23, 0.27);
	glScalef(5, 5, 5);
	obj.Draw();
	glPopMatrix();
	//glutSwapBuffers();


}

void SpaceShip::drawCube()
{
	float size = 5.0f;

	float A[3] = { size,  size,  size };
	float B[3] = { size,  size, -size };
	float C[3] = { size, -size, -size };
	float D[3] = { size, -size,  size };
	float E[3] = { -size,  size,  size };
	float F[3] = { -size,  size, -size };
	float G[3] = { -size, -size, -size };
	float H[3] = { -size, -size,  size };

	float I[3] = { 1.0f,  0.0f,  0.0f };
	float K[3] = { -1.0f,  0.0f,  0.0f };
	float L[3] = { 0.0f,  0.0f, -1.0f };
	float M[3] = { 0.0f,  0.0f,  1.0f };
	float N[3] = { 0.0f,  1.0f,  0.0f };
	float O[3] = { 0.0f, -1.0f,  0.0f };

	glMatrixMode(GL_MODELVIEW);

	//glPushMatrix();
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_QUADS);

	glNormal3fv(I);

	glTexCoord2f(1, 1);
	glVertex3fv(D);
	glTexCoord2f(0, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 0);
	glVertex3fv(B);
	glTexCoord2f(1, 0);
	glVertex3fv(A);

	glNormal3fv(K);

	glTexCoord2f(1, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 1);
	glVertex3fv(H);
	glTexCoord2f(0, 0);
	glVertex3fv(E);
	glTexCoord2f(1, 0);
	glVertex3fv(F);

	glNormal3fv(L);

	glTexCoord2f(1, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 0);
	glVertex3fv(F);
	glTexCoord2f(1, 0);
	glVertex3fv(B);

	glNormal3fv(M);

	glTexCoord2f(1, 1);
	glVertex3fv(H);
	glTexCoord2f(0, 1);
	glVertex3fv(D);
	glTexCoord2f(0, 0);
	glVertex3fv(A);
	glTexCoord2f(1, 0);
	glVertex3fv(E);

	glNormal3fv(N);

	glTexCoord2f(1, 1);
	glVertex3fv(E);
	glTexCoord2f(0, 1);
	glVertex3fv(A);
	glTexCoord2f(0, 0);
	glVertex3fv(B);
	glTexCoord2f(1, 0);
	glVertex3fv(F);

	glNormal3fv(O);

	glTexCoord2f(1, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 0);
	glVertex3fv(D);
	glTexCoord2f(1, 0);
	glVertex3fv(H);

	glEnd();
	//glPopMatrix();
}

