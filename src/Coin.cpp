#include "..\include\Coin.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::drawTorus(int numc, int numt)
{

	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;


	{
		int i, j, k;
		double s, t, x, y, z, twopi;

		twopi = 2 * PI;
		for (i = 0; i < numc; i++) {

			glBegin(GL_QUAD_STRIP);
			for (j = 0; j <= numt; j++) {
				for (k = 1; k >= 0; k--) {
					s = (i + k) % numc + 0.5;
					t = j % numt;

					x = (1 + .1*cos(s*twopi / numc))*cos(t*twopi / numt);
					y = (1 + .1*cos(s*twopi / numc))*sin(t*twopi / numt);
					z = .1 * sin(s * twopi / numc);
					glVertex3f(x, y, z);
				}
			}
			glEnd();

		}
	}
}

//void Coin::timer(int value)
//{
//	const int desiredFPS = 120;
//	//glutTimerFunc(1000 / desiredFPS, timer,++value);
//	GLfloat dt = 1. / desiredFPS;
//
//	//put your specific idle code here
//	//... this code will run at desiredFPS
//	gAngle += dt*360. / 8.; //rotate 360 degrees every 8 seconds
//							//end your specific idle code here
//
//	glutPostRedisplay(); // initiate display() call at desiredFPS rate
//}

void Coin::privateInit()
{
	//quadratic = gluNewQuadric();
	theTorus = glGenLists(1);
	glNewList(theTorus, GL_COMPILE);
	drawTorus(10, 25);
	glEndList();

	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -100.0f));

}

void Coin::privateRender()
{
	//drawTorus(5, 0.5, 10, 5);
	//gluCylinder(quadratic, 0.1f, 0.1f, 3.0f, 32, 32);
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glCallList(theTorus);
	glFlush();

}

void Coin::privateUpdate()
{
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	
	if (testFlag == false) {
		rtri += 0.5f;
		//glRotatef(30., 1.0, 0.0, 0.0);
		//glutPostRedisplay();
	}
	else {
		rtri -= 0.5f;
		//glRotatef(30., 0.0, 1.0, 0.0);
		//glutPostRedisplay();
	}
	if (rtri == 1000.0f)
		testFlag = true;
	if (rtri == 0.0f)
		testFlag = false;
}
