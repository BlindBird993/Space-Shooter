#include <assimp\cimport.h>
#include <assimp\postprocess.h>
#include "SpaceShip.hpp"
#include "SOIL.h"

SpaceShip::SpaceShip(std::shared_ptr<Skybox> skybox_)
{
	this->skybox_ = skybox_;
	this->currentWeapon = "MachineGun";
	machinegunBullets = 100;
	laserBullets = 100;
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

void SpaceShip::drawTorus(double r, double c, int rSeg, int cSeg)
{

	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;

	for (int i = 0; i < rSeg; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= cSeg; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg + 0.5;
				double t = j % (cSeg + 1);

				double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
				double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
				double z = r * sin(s * TAU / rSeg);

				double u = (i + k) / (float)rSeg;
				double v = t / (float)cSeg;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}

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

//bool SpaceShip::loadModel(const char * path,
//	std::vector < glm::vec3 > & out_vertices,
//	std::vector < glm::vec2 > & out_uvs,
//	std::vector < glm::vec3 > & out_normals)
//{
//	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
//	std::vector< glm::vec3 > temp_vertices;
//	std::vector< glm::vec2 > temp_uvs;
//	std::vector< glm::vec3 > temp_normals;
//
//	FILE * file = fopen(path, "r");
//	if (file == NULL) {
//		printf("Impossible to open the file !\n");
//		return false;
//	}
//	while (1) {
//
//		char lineHeader[128];
//		// read the first word of the line
//		int res = fscanf(file, "%s", lineHeader);
//		if (res == EOF)
//			break; // EOF = End Of File. Quit the loop.
//
//				   // else : parse lineHeader
//		if (strcmp(lineHeader, "v") == 0) {
//			glm::vec3 vertex;
//			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//			temp_vertices.push_back(vertex);
//		}
//		else if (strcmp(lineHeader, "vt") == 0) {
//			glm::vec2 uv;
//			fscanf(file, "%f %f\n", &uv.x, &uv.y);
//			temp_uvs.push_back(uv);
//		}
//		else if (strcmp(lineHeader, "vn") == 0) {
//			glm::vec3 normal;
//			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
//			temp_normals.push_back(normal);
//		}
//		else if (strcmp(lineHeader, "f") == 0) {
//			std::string vertex1, vertex2, vertex3;
//			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//			if (matches != 9) {
//				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//				return false;
//			}
//			vertexIndices.push_back(vertexIndex[0]);
//			vertexIndices.push_back(vertexIndex[1]);
//			vertexIndices.push_back(vertexIndex[2]);
//			uvIndices.push_back(uvIndex[0]);
//			uvIndices.push_back(uvIndex[1]);
//			uvIndices.push_back(uvIndex[2]);
//			normalIndices.push_back(normalIndex[0]);
//			normalIndices.push_back(normalIndex[1]);
//			normalIndices.push_back(normalIndex[2]);
//
//
//	return false;
//}



void SpaceShip::privateInit()
{

	//model load
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

	spaceshipShader_.initShaders("../Shaders/reflection");
	spaceshipShader_.enable();

	GLint texture1 = glGetUniformLocation(spaceshipShader_.getProg(), "cube_texture");//fragment
	glUniform1i(texture1, 0);

	if (cubeTextures_ == NULL) { std::cout << "Fail" << std::endl; }

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f));
	spaceshipShader_.disable();
}

void SpaceShip::privateRender()
{

	spaceshipShader_.enable();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cubeTextures_);
	

	drawCube();
	//glCallList(list_id);
	//drawTorus(3.0f, 6.0f, 64, 32);
	
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);


	spaceshipShader_.disable();
	//std::cout << matrix_[3][0] << ' ' << matrix_[3][1] << ' ' << matrix_[3][2] << std::endl;

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

