
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::privateInit()
{

	//const char *texturePath = "../textures/colormap.bmp";
	//BMPLoad(texturePath, textureClass_);
	//glGenTextures(1, &textureName_);
	//glBindTexture(GL_TEXTURE_2D, textureName_);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, textureClass_.width, textureClass_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureClass_.bytes);

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 15.0f, -5.0f));

}

void Enemy::privateRender()
{
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureName_);

	glColor3f(1.0f, 0.0f, 0.0f);
	float size = 5.0f;
	glBegin(GL_QUADS);
	// Near Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	glEnd();

	//glDisable(GL_TEXTURE_2D);

}

void Enemy::privateUpdate()
{
//move object

	if (checkFlag == false) {
		z_coord -= 1.0;
		y_coord -= 1.0;
	}
	if (checkFlag == true) {
		z_coord += 1.0;
		y_coord += 1.0;
	}
	//std::vector<float>pos {x,y,z};
	if (z_coord <= min_z && y_coord <= min_y) {
		checkFlag = true;
	}
	if (z_coord >= max_z && y_coord >= max_y) {
		checkFlag = false;
	}
	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, y_coord, -z_coord));

}

