#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <GL/glew.h>  
#include <GL/freeglut.h>
#include <soil/SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"
#include "glm/glm.hpp"
#include "ShaderTest.h"
#include "FPSCounter.h"
#include <iostream>

std::shared_ptr<GameManager> gm;
//siut::FpsCounter counter;
std::shared_ptr<FPSCounter> fpscounter;

int window;

bool keyPressed[30];
int mousePosX, mousePosY;
float moveX, moveY;

void getFps(int x, int y, std::string text);
//float nextShooting;
//const float secondsForShooting = 0.2f;

void init()//preinitialization before rendering
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	fpscounter = std::make_shared<FPSCounter>();

	GLenum err = glewInit();

	//counter.start();//start of fps counter
	fpscounter->CalculateFrameRate();
	//nextShooting = fpscounter->getCurrentTime() + secondsForShooting;

	gm.reset(new GameManager());
	gm->init();//game manager initialization

	for (int i = 0; i < 30; i++)
		keyPressed[i] = false;//setting key events to false
}

void display()//rendering
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clearing the scene

	gm->update(1);
	gm->render();
	fpscounter->CalculateFrameRate();
	getFps(900, 735, "FPS: " + std::to_string(int(fpscounter->fps_)));
	getFps(5, 735, "MachineGun: " + std::to_string(gm->getSpaceShip()->getMachineGunAmount()));
	getFps(5, 690, "Laser: " + std::to_string(gm->getSpaceShip()->getLaserAmount()));
	getFps(890, 700, "Life: " + std::to_string(gm->getSpaceShip()->getLife()));
	getFps(850, 670, "Armor: " + std::to_string(gm->getSpaceShip()->getArmor()));
	getFps(450, 735, "Score: " + std::to_string(gm->score_));

	gm->setCurrentTime(fpscounter->getCurrentTime());

	//if (keyPressed[KEY_ID_W] == true) {
	//	gm->getCam()->moveForward();
	//	gm->getSpaceShip()->shipMoveForward();
	//}
	if (keyPressed[KEY_ID_A] == true) {
		gm->getSpaceShip()->shipMoveLeft();
		gm->getCam()->moveLeft();
	}
	if (keyPressed[KEY_ID_D] == true) {
		gm->getSpaceShip()->shipMoveRight(); 
		gm->getCam()->moveRight();
	}

	//if (keyPressed[KEY_ID_S] == true) {
	//	gm->getSpaceShip()->shipMoveBackward();
	//	gm->getCam()->moveBackward();

	//}
	//if (keyPressed[KEY_ID_SPACE] == true) {

	//	//gm->getSpaceShip()->shipMoveUp();
	//	gm->getCam()->moveUp();
	//}
	//if (keyPressed[KEY_ID_C] == true) {

	//	//gm->getSpaceShip()->shipMoveDown();
	//	gm->getCam()->moveDown();
	//}
	//ship movement
	/*if (keyPressed[KEY_ID_RIGHT] == true)  gm->getSpaceShip()->shipMoveRight();
	if (keyPressed[KEY_ID_LEFT] == true)   gm->getSpaceShip()->shipMoveLeft();

	if (keyPressed[KEY_ID_FORWARD] == true)  gm->getSpaceShip()->shipMoveForward();
	if (keyPressed[KEY_ID_BACKWARD] == true) {
		gm->getSpaceShip()->shipMoveBackward();
	}*/
	//fire
	//if (keyPressed[KEY_ID_Z] == true) {

	//	//if (fpscounter->getCurrentTime() >= nextShooting) {
	//		//nextShooting += secondsForShooting;
	//	gm->weaponFire();
	//	//}
	//}
	//reload
	if (keyPressed[KEY_ID_F] == true) gm->getSpaceShip()->reload();

	if (keyPressed[KEY_ID_1] == true) gm->getSpaceShip()->changeWeapon("MachineGun");

	if (keyPressed[KEY_ID_2] == true) {
  	  gm->getSpaceShip()->changeWeapon("Laser");
    }

	if (keyPressed[KEY_ID_O] == true) {
		//gm->addEnemies();
	}
	if (keyPressed[KEY_ID_P] == true) {
		gm->weaponFire();
	}


	glutSwapBuffers();//swap buffer objects ?
	glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 27:
		glutDestroyWindow(window);
#ifndef _WIN32
		// Must use this with regular glut, since it never returns control to main().
		exit(0);
#endif
		break;

	//case 'w':
	//	keyPressed[KEY_ID_W] = true;
	//	break;
	case 'a':
		keyPressed[KEY_ID_A] = true;
		break;
	//case 's':
	//	keyPressed[KEY_ID_S] = true;
	//	break;
	case 'd':
		keyPressed[KEY_ID_D] = true;
		break;
	//case ' ':
	//	keyPressed[KEY_ID_SPACE] = true;
	//	break;
	//case 'c':
	//	keyPressed[KEY_ID_C] = true;
	//	break;

	//case 't':
	//	keyPressed[KEY_ID_RIGHT] = true;
	//	break;
	//case 'y':
	//	keyPressed[KEY_ID_LEFT] = true;
	//	break;

	//case 'u':
	//	keyPressed[KEY_ID_UP] = true;
	//	break;
	//case 'j':
	//	keyPressed[KEY_ID_DOWN] = true;
	//	break;

	//case 'g':
	//	keyPressed[KEY_ID_FORWARD] = true;
	//	break;
	//case 'b':
	//	keyPressed[KEY_ID_BACKWARD] = true;
	//	break;
		//fire
	//case 'z':
	//	keyPressed[KEY_ID_Z] = true;
	//	break;
	case 'f':
		keyPressed[KEY_ID_F] = true;
		break;

	//case 'x':
	//	keyPressed[KEY_ID_X] = true;
	//	break;

	case 'o':
		keyPressed[KEY_ID_O] = true;
		break;
	case 'p':
		keyPressed[KEY_ID_P] = true;
		break;

	case '1':
		keyPressed[KEY_ID_1] = true;
		break;
	case '2':
		keyPressed[KEY_ID_2] = true;
		break;

	default:
		glutPostRedisplay();
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	/*case 'w':
		keyPressed[KEY_ID_W] = false;
		break;*/
	case 'a':
		keyPressed[KEY_ID_A] = false;
		break;
	/*case 's':
		keyPressed[KEY_ID_S] = false;
		break;*/
	case 'd':
		keyPressed[KEY_ID_D] = false;
		break;
	/*case ' ':
		keyPressed[KEY_ID_SPACE] = false;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = false;
		break;

	case 't':
		keyPressed[KEY_ID_RIGHT] = false;
		break;
	case 'y':
		keyPressed[KEY_ID_LEFT] = false;
		break;

	case 'u':
		keyPressed[KEY_ID_UP] = false;
		break;
	case 'j':
		keyPressed[KEY_ID_DOWN] = false;
		break;

	case 'g':
		keyPressed[KEY_ID_FORWARD] = false;
		break;
	case 'b':
		keyPressed[KEY_ID_BACKWARD] = false;
		break;*/
		//fire
	//case 'z':
	//	keyPressed[KEY_ID_Z] = false;
	//	break;
	case 'f':
		keyPressed[KEY_ID_F] = false;//reload
		break;

	//case 'x':
	//	keyPressed[KEY_ID_X] = false;
	//	break;

	case 'o':
		keyPressed[KEY_ID_O] = false;
		break;
	case 'p':
		keyPressed[KEY_ID_P] = false;
		break;

	case '1':
		keyPressed[KEY_ID_1] = false;
		break;
	case '2':
		keyPressed[KEY_ID_2] = false;
		break;

	}
}

void mousePressed(int button, int state, int posX, int posY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mousePosX = posX;
		mousePosY = posY;
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
	if (keyPressed[MOUSE_LEFT_BUTTON_DOWN])
	{
		int diffX = posX - mousePosX;
		mousePosX = posX;
		int diffY = posY - mousePosY;
		mousePosY = posY;

		// Implement quaternion based mouse move

	}
}

void reshape(int w, int h)//resize
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//  glOrtho(-50, 700, -50, 700, -50, 50);
	gluPerspective(60.0f, float(w) / float(h), 1.0f, 3000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}


int printOglError(char *file, int line)
{
	//
	// Returns 1 if an OpenGL error occurred, 0 otherwise.
	//
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}

int main(int argc, char** argv)
{


	int success = 0;
	int gl_major, gl_minor;
	GLchar *VertexShaderSource, *FragmentShaderSource;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(10, 10);
	window = glutCreateWindow("My Space Shooter");

	init();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);

	//readShaderSource("../Shaders/red", &VertexShaderSource, &FragmentShaderSource);
	//success = installShaders(VertexShaderSource, FragmentShaderSource);
	//success *= initRedShader();

	// Add other callback functions here..

	glutMainLoop();
	return 0;
}

void getFps(int x, int y, std::string text)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	char string[64];
	//sprintf(string, "something");
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1024, 0, 768, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
