#include "Bullets.h"

Bullets::Bullets(std::string type, glm::mat4 position, bool friendly, int depth)
{
	this->type_ = type;
	if (type_ == "MachineGun") {
		life_ = 100;
		damage_ = 3;
	}
	if (type_ == "Laser") {
		life_ = 150;
		damage_ = 5;
	}
	this->position_ = position[3];
	this->friendly_ = friendly;
	this->depth_ = depth;
	this->maxX = 7;
	this->minX = 0;
	this->maxY = 7;
	this->minY = 0;
	this->maxZ = position_.z - 7;
	this->minZ = position_.z;

	privateInit();
}

Bullets::~Bullets()
{
}

glm::vec3 Bullets::getPosition()
{
	return position_;
}

void Bullets::createBullets()
{
	auto x = position_.x;
	auto y = position_.y;
	auto z = position_.z;
	

	if (friendly_ == false)
	{
		z = -depth_ + position_.z;
	}

	if (type_ == "MachineGun")
	{
		increment = 0.2f;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.00, 1.00, 0.00);

		glBegin(GL_QUADS);
		glVertex3f(x + increment, y + increment, z + increment);
		glVertex3f(x - increment, y + increment, z + increment);
		glVertex3f(x - increment, y - increment, z + increment);
		glVertex3f(x + increment, y - increment, z + increment);
		glEnd();

		//std::cout << position_[0] << " " << position_[1] << std::endl;
	}

	if (type_ == "Laser")
	{
		increment = 0.1f;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.00, 0.00, 1.00);

		glBegin(GL_QUADS);
		glVertex3f(x + increment, y + increment, z + increment);
		glVertex3f(x - increment, y + increment, z + increment);
		glVertex3f(x - increment, y - increment, z + increment);
		glVertex3f(x + increment, y - increment, z + increment);
		glEnd();
		std::cout << position_[0] << " " << position_[1] << std::endl;
	}
}


void Bullets::privateInit()
{
	bullets = glGenLists(1);
	glNewList(bullets, GL_COMPILE);
	createBullets();
	glEndList();

	//glShadeModel(GL_FLAT);
	//glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Bullets::privateRender()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	glCallList(bullets);
	glFlush();
}

void Bullets::privateUpdate()
{
	if (friendly_ == true) {
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -6.0f));
	}
	else
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 6.0f));
	life_--;

	//from -4 to -inf
	// x and y always 0
	//std::cout << matrix_[3][2] << " " << matrix_[3][0] << " " << matrix_[3][1] << std::endl;
	//std::cout << getRadius()  << std::endl;
	//std::cout << this->matrix_[3][0] <<" "<< this->matrix_[3][1] << std::endl;

	//std::cout << getPos()[0] << " " << getPos()[1] << " " << getPos()[2] << std::endl;
}

glm::vec3 Bullets::getPos() const
{
	return glm::vec3(position_[0], position_[1], matrix_[3][2]);
}

float Bullets::getRadius() const
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
