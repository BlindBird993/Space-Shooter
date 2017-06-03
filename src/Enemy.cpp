#pragma once
#include "Enemy.h"

Enemy::Enemy(std::string type, float speed, int xBoundary, float startPos)
{
	this->type_ = type;
	this->xBoundary_ = xBoundary;
	this->xPos_ = std::abs(xBoundary_ / 2);
	this->startPos_ = startPos * -1;
	
	if (type_ == "ordinary") {
		color_ = { 1.0f,0.0f,0.0f };
		this->currentWeapon = "MachineGun";
		this->life_ = 50;
		this->speed_ = speed;

	}
	if (type_ == "heavy") {
		color_ = { 0.0f,1.0f,0.0f };
		this->currentWeapon = "MachineGun";
		this->life_ = 100;
		this->speed_ = speed-1;

	}
	if (type_ == "boss") {
		color_ = { 0.0f,0.0f,1.0f };
		this->currentWeapon = "Laser";
		this->life_ = 200;
		this->speed_ = speed;

	}

	maxX = 10;
	minX = 0;
	maxY = 10;
	minY = 0;
	maxZ = startPos_+10;
	minZ = startPos_;
	
	privateInit();
}

Enemy::~Enemy()
{
}

std::vector<std::vector<float>> Enemy::getVertexArr()
{
	return vertexArray_;
}

bool Enemy::getEnemyStatus()
{
	return isActive_;
}

void Enemy::setWeapon(std::string weapon)
{
	this->currentWeapon = weapon;
}

std::string Enemy::getWeapon() const
{
	return this->currentWeapon;
}

//get position
glm::vec3 Enemy::getPos() const
{
	return glm::vec3(matrix_[3][0], matrix_[3][1], matrix_[3][2]);
}


float Enemy::getRadius() const
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

void Enemy::createEnemy()
{
	glColor3f(color_[0],color_[1],color_[2]);
	float size = 5.0f;

	glBegin(GL_QUADS);
	glNormal3f(5.0f, 5.0f, -512.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, startPos_);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, startPos_);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, startPos_);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, startPos_);

	glEnd();
}

bool Enemy::shoot()
{
	if (bulletAmount > 0) {
		bulletAmount--;
		return true;
	}
	return false;
}

int Enemy::getAmmo()
{
	return bulletAmount;
}

void Enemy::setAmmo(int ammo)
{
	bulletAmount = ammo;
}


void Enemy::move()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}

void Enemy::privateInit()
{

	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);
	createEnemy();
	glEndList();

	

	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	////list_id = glGenLists(1);
	////glNewList(list_id, GL_COMPILE);//begin new list
	//static const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f, // triangle 1 : end

	//	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f, // triangle 2 : end

	//	1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	1.0f,-1.0f,-1.0f,

	//	1.0f, 1.0f,-1.0f,
	//	1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,

	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,

	//	1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,

	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	1.0f,-1.0f, 1.0f,

	//	1.0f, 1.0f, 1.0f,
	//	1.0f,-1.0f,-1.0f,
	//	1.0f, 1.0f,-1.0f,

	//	1.0f,-1.0f,-1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f,-1.0f, 1.0f,

	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f,

	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,

	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	1.0f,-1.0f, 1.0f
	//};
	////glEndList();//end new list

	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 5.0f, -5.0f));

}

void Enemy::privateRender()
{
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureName_);
	
	glCallList(list_id);
	glFlush();

	//glColor3f(1.0f, 1.0f, 0.0f);
	//float size = 5.0f;

	//glBegin(GL_TRIANGLES);
	//glNormal3f(5.0f, 5.0f, -512.0f);

	//glVertex3f(-5.0f, height_, zStart_);
	//glVertex3f(5.0f, height_, zStart_);
	//glVertex3f(5.0f, height_ + 5.0f, zStart_);


	//glEnd();


	
	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 15.0f, z_coord));
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	////
	//glDisableVertexAttribArray(0);

	//glDisable(GL_TEXTURE_2D);

}

void Enemy::privateUpdate()
{
//move object

	//if (checkFlag == false) {
	//	z_coord -= 1.0;
	//	//y_coord -= 1.0;
	//}
	//if (checkFlag == true) {
	//	z_coord += 1.0;
	//	//y_coord += 1.0;
	//}
	////std::vector<float>pos {x,y,z};
	//if (z_coord <= min_z){ //&& y_coord <= min_y) {
	//	checkFlag = true;
	//}
	//if (z_coord >= max_z){ //&& y_coord >= max_y) {
	//	checkFlag = false;
	//}
	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 15.0f, z_coord));
	float max_x = xBoundary_;
	float min_x = xBoundary_*-1;

	matrix_ = glm::translate(glm::mat4(), glm::vec3(xPos_, max_y, (speed_*0.5f) * z_coord));

	// Z-direction
	z_coord ++;

	// X-direction
	if (checkFlag == false) xPos_++;
	else xPos_--;

	if (xPos_ == max_x) checkFlag = true;
	if (xPos_ == min_x) checkFlag = false;
	
	//from 0 to 512
	//std::cout << matrix_[3][2] << std::endl;
	//std::cout << matrix_[3][0] <<" "<< matrix_[3][1] << std::endl;
	//std::cout << getRadius() << std::endl;

}



