#include "..\include\Coin.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::timer(int value)
{
	const int desiredFPS = 120;
	//glutTimerFunc(1000 / desiredFPS, timer,++value);
	GLfloat dt = 1. / desiredFPS;

	//put your specific idle code here
	//... this code will run at desiredFPS
	gAngle += dt*360. / 8.; //rotate 360 degrees every 8 seconds
							//end your specific idle code here

	glutPostRedisplay(); // initiate display() call at desiredFPS rate
}

void Coin::privateInit()
{
	quadratic = gluNewQuadric();


}

void Coin::privateRender()
{
	gluCylinder(quadratic, 0.1f, 0.1f, 3.0f, 32, 32);
}

void Coin::privateUpdate()
{
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
}
