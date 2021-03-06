#include "..\include\AmmoGun.h"

AmmoGun::AmmoGun(float startPos, float xPos)
{
	this->xPos_ = xPos;
	this->startPos_ = startPos * -1;
	maxX = 10;
	minX = 0;
	maxY = 10;
	minY = 0;
	maxZ = startPos_ + 10;
	minZ = startPos_;
}

AmmoGun::~AmmoGun()
{
}

void AmmoGun::privateInit()
{
	ammoShader_.initShaders("../Shaders/phong");
	ammoShader_.enable();

	glUniform3f(glGetUniformLocation(ammoShader_.getProg(), "ObjColor"), 1.000f, 0.843f, 0.000f);
	glUniform3f(glGetUniformLocation(ammoShader_.getProg(), "LightPosition"), -1.0, -100.0, 3.0);

	ammoShader_.disable();
	matrix_ = glm::translate(matrix_, glm::vec3(xPos_, 175.0f, -startPos_));

}

void AmmoGun::privateRender()
{
	ammoShader_.enable();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glRotatef(xRotated, 1.0, 0.0, 0.0);
	//glPushMatrix();
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(20.0, 150, 150);
	//glPopMatrix();
	//drawCube();
	ammoShader_.disable();
}

void AmmoGun::privateUpdate()
{
	if (testFlag == false)
		rtri += 0.5f;
	else
		rtri -= 0.5f;
	if (rtri == 1000.0f)
		testFlag = true;
	if (rtri == 0.0f)
		testFlag = false;

	
	//startPos_--;
	//std::cout << getPos()[0] <<" " << getPos()[1] << std::endl;
}

void AmmoGun::drawCube()
{
	float size = 3.0f;

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

	glPushMatrix();
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);

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
	glPopMatrix();
}

glm::vec3 AmmoGun::getPos() const
{
	return glm::vec3(matrix_[3][0], matrix_[3][1], matrix_[3][2]);
}

glm::vec3 AmmoGun::getDS() const
{
	return glm::vec3();
}

float AmmoGun::getRadius() const
{
	auto eps = 1e-5;

	float centX1, centY1, centZ1, radius;

	if ((minX + maxX) / 2 < eps) centX1 = 0;
	else centX1 = (minX + maxX) / 2;

	if ((minY + maxY) / 2 < eps) centY1 = 0;
	else centY1 = (minY + maxY) / 2;

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
