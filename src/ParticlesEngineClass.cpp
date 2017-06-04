#include "ParticlesEngineClass.h"



ParticlesEngineClass::ParticlesEngineClass(GLuint textureName, glm::mat4 matrix)
{
	textureName_ = textureName;
	this->matrix_ = matrix;
}


ParticlesEngineClass::~ParticlesEngineClass()
{
}

void ParticlesEngineClass::privateInit()
{
	//particle init
	for (loop = 0; loop < MAX_PARTICLES; loop++)				
	{
		
		particlesArray_[loop].active = true;										
		particlesArray_[loop].life = 1.0f;											
		particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;		

		particlesArray_[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];			
		particlesArray_[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];			
		particlesArray_[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];			

		particlesArray_[loop].xi = float((rand() % 50) - 25.0f)*10.0f;				
		particlesArray_[loop].yi = float((rand() % 50) - 25.0f)*10.0f;				
		particlesArray_[loop].zi = 300 + float((rand() % 60) - 30.0f);		

	}

}

void ParticlesEngineClass::privateRender()
{
	glShadeModel(GL_SMOOTH);								
	glClearDepth(1.0f);										
	glDisable(GL_DEPTH_TEST);								
	glEnable(GL_BLEND);										
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);						
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				
	glEnable(GL_TEXTURE_2D);								
	glBindTexture(GL_TEXTURE_2D, textureName_);					

	for (loop = 0; loop < MAX_PARTICLES; loop++)					
	{
		if (particlesArray_[loop].active) {						

			float x = particlesArray_[loop].x;						
			float y = particlesArray_[loop].y;						
			float z = particlesArray_[loop].z;				

													
			glColor4f(particlesArray_[loop].r, particlesArray_[loop].g, particlesArray_[loop].b, particlesArray_[loop].life);

			glBegin(GL_TRIANGLE_STRIP);								
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z);	
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);	
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);	
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);	
			glEnd();												

			particlesArray_[loop].x += particlesArray_[loop].xi / (2.0f * 5000);	
			particlesArray_[loop].y += particlesArray_[loop].yi / (2.0f * 5000);	
			particlesArray_[loop].z += particlesArray_[loop].zi / (2.0f * 5000);	

																	
			particlesArray_[loop].yi += particlesArray_[loop].yg;				

			particlesArray_[loop].life -= particlesArray_[loop].fade;			

																
			if (particlesArray_[loop].life < 0.0f)											
			{
				particlesArray_[loop].life = 1.0f;											
				particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;		
				particlesArray_[loop].x = 0.0f;											
				particlesArray_[loop].y = 0.0f;											
				particlesArray_[loop].z = 0.0f;											

																					
				particlesArray_[loop].zi = 300 + float((rand() % 60) - 30.0f);				

				particlesArray_[loop].r = colors[0][0];			
				particlesArray_[loop].g = colors[0][1];			
				particlesArray_[loop].b = colors[0][2];			
			}
		}
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

}

void ParticlesEngineClass::privateUpdate()
{
}
