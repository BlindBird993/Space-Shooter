#include "BattleField.hpp"
#include "SOIL.h"


BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	auto glmVec = glm::vec3{};
	int CONST_SIZE_X = 32;
	int CONST_SIZE_Z = 512;
	float x_coord = 0.0;
	float z_coord = 0.0;
  // Create vertex array
	for (int i = 0; i < CONST_SIZE_Z; i++) {		
		
		for (int j = 0; j < CONST_SIZE_X; j++) {
	
			x_coord = (j * 10) - 160;
			z_coord = (i*-10);

			this->vertexArray_.push_back(glm::vec3(x_coord,0.0,z_coord));
		}

	}
	//Create texture array
	for (double i = 0; i < CONST_SIZE_Z; i++) {

		for (double j = 0; j < CONST_SIZE_X; j++) {

			x_coord = (j / (CONST_SIZE_X -1));
			z_coord = (i / (CONST_SIZE_Z - 1));

			this->textureArray_.push_back(glm::vec2(x_coord,z_coord));
		}

	}
	//set primitive restart values
	glPrimitiveRestartIndex(MAXUINT);
	//build index array
	for (int i = 0; i < CONST_SIZE_Z-1; i++) {

		for (int j = 0; j < CONST_SIZE_X; j++) {

			this->indexArray_.push_back((j+CONST_SIZE_X)+ (CONST_SIZE_X*i));
			this->indexArray_.push_back(j+(CONST_SIZE_X*i));

		}
		this->indexArray_.push_back(MAXUINT);
	}
	int a = 7;
	//texture initiation
	/*
	const char *texturePath = "../textures/colormap.bmp";
	BMPLoad(texturePath, textureClass_);
	glGenTextures(1, &textureName_);
	glBindTexture(GL_TEXTURE_2D, textureName_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureClass_.width, textureClass_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureClass_.bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
	*/

	int width, height;

	unsigned char* img = SOIL_load_image("../textures/colormap.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	
	glGenTextures(1, &textureName_);
	glBindTexture(GL_TEXTURE_2D, textureName_);
	
	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;
	
	if (textureName_ == NULL) {

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

	//textureName_ = SOIL_load_OGL_texture(
	//	".. / textures / colormap.bmp",
	//	SOIL_LOAD_AUTO,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	//		
	//	);
	//if (textureName_ == 0) {
	//
	//	printf("Error in download '%s'", SOIL_last_result());
	//}


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	////glTexImage2D(GL_TEXTURE_2D, 0, 3, textureClass_.width, textureClass_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureClass_.bytes);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//GLuint tex_2d = SOIL_load_OGL_texture
	//	(
	//		"C:/Users/Igor Molchanov/Documents/Visual Studio 2015/Projects/SpaceShooter/textures/colormap.bmp",
	//		SOIL_LOAD_AUTO,
	//		SOIL_CREATE_NEW_ID,
	//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT
	//		);

	//if (0 == tex_2d)
	//{
	//	printf("SOIL loading error: '%s'\n", SOIL_last_result());
	//}
}

void BattleField::privateRender()
{

	glEnable(GL_PRIMITIVE_RESTART);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName_);
  // Render the battlefield
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureArray_[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);

	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_PRIMITIVE_RESTART);
	//texture
	


	//glEnd();

	// Enable texturing before render
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureName_);
	//glEnable(GL_PRIMITIVE_RESTART);
	//// Render the battlefield
	//glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
	//glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]); // set vertex pointer
	//glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]); //strips
	//																					 //glDrawArrays (GL_POINTS,0,vertexArray_.size());
	//glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
	//glDisable(GL_PRIMITIVE_RESTART);

	//glBindTexture(GL_TEXTURE_2D, 0); //unbind texture
	//glDisable(GL_TEXTURE_2D);
	
}

void BattleField::privateUpdate()
{
}

