#include "Bullets.h"

Bullets::Bullets(Weapon * weapon, glm::mat4 position, bool friendly, int depth)
{
	this->type_ = weapon->getName();
	this->life_ = weapon->getRange();
	this->position_ = position[3];
	this->friendly_ = friendly;
	this->depth_ = depth;
}

Bullets::~Bullets()
{
}

glm::vec3 Bullets::getPosition()
{
	return position_;
}

std::vector< std::vector<float>> Bullets::getVertexArr()
{
	return vertexArray_;
}

void Bullets::privateInit()
{
}

void Bullets::privateRender()
{
	auto x = position_.x;
	auto y = position_.y;
	auto z = position_.z;
	float increment = 0.2f;

	if (friendly_ == false)
	{
		z = -depth_ + position_.z;
	}

	if (type_ == "MachineGun")
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.00, 1.00, 0.00);

		glBegin(GL_QUADS);
		glVertex3f(x + increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y + increment, z + increment});
		glVertex3f(x - increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y + increment, z + increment});
		glVertex3f(x - increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y - increment, z + increment});
		glVertex3f(x + increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y - increment, z + increment});
		glEnd();
	}

	if (type_ == "Lazer")
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.00, 0.00, 0.00);

		glBegin(GL_QUADS);
		glVertex3f(x + increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{ x + increment, y + increment, z + increment});
		glVertex3f(x - increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y + increment, z + increment});
		glVertex3f(x - increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{ x - increment, y - increment, z + increment});
		glVertex3f(x + increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{ x + increment, y - increment, z + increment});
		glEnd();
	}
}

void Bullets::privateUpdate()
{
	if (friendly_ == true) {
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -7.0f)); 
	}
	else 
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 7.0f));
	life_--;
}
