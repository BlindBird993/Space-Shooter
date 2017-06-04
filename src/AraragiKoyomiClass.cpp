//#include "AraragiKoyomiClass.h"
//
//
//
//AraragiKoyomiClass::AraragiKoyomiClass()
//{
//}
//
//
//AraragiKoyomiClass::~AraragiKoyomiClass()
//{
//}
//
//
//
//void AraragiKoyomiClass::privateInit()
//{
//	//download texture
//	int width, height;
//
//	unsigned char* image = SOIL_load_image("../textures/araragi.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//
//	glGenTextures(1, &texture_);
//	glBindTexture(GL_TEXTURE_2D, texture_);
//
//	if (!image)
//		std::cout << "Not loaded" << sizeof(image) << std::endl;
//
//	if (texture_ == NULL) {
//
//		printf("Error in download '%s'", SOIL_last_result());
//	}
//	else {
//		std::cout << "Texture loaded, Araragi: " << "size " << sizeof(image) << " height " << height << " width " << width << std::endl;
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//
//		SOIL_free_image_data(image);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//	}
//	//end
//	//vertex array
//	GLfloat VArray[] = { 0.0f, 0.0f, 1.0f, };
//
//	//display list
//	list_id = glGenLists(1);
//	glNewList(list_id, GL_COMPILE);//begin new list
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//	float size = 5.0f;
//
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
//	glEnd();
//
//	glEndList();//end new list
//				//end
//	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -255.0f));
//}
//
//void AraragiKoyomiClass::privateRender()
//{
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texture_);
//
//	glCallList(list_id);
//
//	glBegin(GL_QUADS);
//
//	glTexCoord2f(0, 0);
//	glVertex3f(0, 0, -2);
//
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 0, -2);
//
//	glTexCoord2f(1, 1);
//	glVertex3f(1, 1, -2);
//
//	glTexCoord2f(0, 1);
//	glVertex3f(0, 1, -2);
//
//	glEnd();
//
//	glDisable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//}
//
//void AraragiKoyomiClass::privateUpdate()
//{
//}
