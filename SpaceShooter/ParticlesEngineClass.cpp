#include "ParticlesEngineClass.h"



ParticlesEngineClass::ParticlesEngineClass()
{
}


ParticlesEngineClass::~ParticlesEngineClass()
{
}

void ParticlesEngineClass::privateInit()
{
	//const char *texturePath = "../textures/colormap.bmp";
	//BMPLoad(texturePath, textureClass_);
	//glGenTextures(1, &textureName_);
	//glBindTexture(GL_TEXTURE_2D, textureName_);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, textureClass_.width, textureClass_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureClass_.bytes);

	//particle init
	for (loop = 0; loop<MAX_PARTICLES; loop++)				// Initials All The Textures
	{
		particlesArray_[loop].active = true;								// Make All The Particles Active
		particlesArray_[loop].life = 1.0f;								// Give All The Particles Full Life
		particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
		particlesArray_[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particlesArray_[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particlesArray_[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particlesArray_[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
		particlesArray_[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
		particlesArray_[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
		particlesArray_[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
		particlesArray_[loop].yg = -0.8f;								// Set Vertical Pull Downward
		particlesArray_[loop].zg = 0.0f;									// Set Pull On Z Axis To Zero
	}
	//end



	//for (loop = 0; loop<500; loop++) // Initials All The Textures 

	//{
	//	particlesArray_[loop].active = true; // Make All The Particles Active 
	//	particlesArray_[loop].life = 1.0f; // Give All The Particles Full Life 
	//	particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f; // Random Fade Speed 
	//	particlesArray_[loop].r = colors[loop*(12 / MAX_PARTICLES)][0]; // Select Red Rainbow Color 
	//	particlesArray_[loop].g = colors[loop*(12 / MAX_PARTICLES)][1]; // Select Red Rainbow Color 
	//	particlesArray_[loop].b = colors[loop*(12 / MAX_PARTICLES)][2]; // Select Red Rainbow Color 
	//	particlesArray_[loop].xi = float((rand() % 50) - 26.0f)*10.0f; // Random Speed On X Axis 
	//	particlesArray_[loop].yi = float((rand() % 50) - 25.0f)*10.0f; // Random Speed On Y Axis 
	//	particlesArray_[loop].zi = float((rand() % 50) - 25.0f)*10.0f; // Random Speed On Z Axis 
	//	particlesArray_[loop].xg = 0.0f; // Set Horizontal Pull To Zero 
	//	particlesArray_[loop].yg = -0.8f; // Set Vertical Pull Downward 
	//	particlesArray_[loop].zg = 0.0f; // Set Pull On Z Axis To Zero 
	//}



}

void ParticlesEngineClass::privateRender()
{

	for (loop = 0; loop<MAX_PARTICLES; loop++)					// Loop Through All The Particles
	{
		if (particlesArray_[loop].active)							// If The Particle Is Active
		{
			float x = particlesArray_[loop].x;						// Grab Our Particle X Position
			float y = particlesArray_[loop].y;						// Grab Our Particle Y Position
			float z = particlesArray_[loop].z + zoom;					// Particle Z Pos + Zoom

																		 //Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particlesArray_[loop].r, particlesArray_[loop].g, particlesArray_[loop].b, particlesArray_[loop].life);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particlesArray_[loop].x += particlesArray_[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
			particlesArray_[loop].y += particlesArray_[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
			particlesArray_[loop].z += particlesArray_[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

			particlesArray_[loop].xi += particlesArray_[loop].xg;			// Take Pull On X Axis Into Account
			particlesArray_[loop].yi += particlesArray_[loop].yg;			// Take Pull On Y Axis Into Account
			particlesArray_[loop].zi += particlesArray_[loop].zg;			// Take Pull On Z Axis Into Account
			particlesArray_[loop].life -= particlesArray_[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particlesArray_[loop].life<0.0f)					// If Particle Is Burned Out
			{
				particlesArray_[loop].life = 1.0f;					// Give It New Life
				particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
				particlesArray_[loop].x = 0.0f;						// Center On X Axis
				particlesArray_[loop].y = 0.0f;						// Center On Y Axis
				particlesArray_[loop].z = 0.0f;						// Center On Z Axis
				particlesArray_[loop].xi = xspeed + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
				particlesArray_[loop].yi = yspeed + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
				particlesArray_[loop].zi = float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
				particlesArray_[loop].r = colors[col][0];			// Select Red From Color Table
				particlesArray_[loop].g = colors[col][1];			// Select Green From Color Table
				particlesArray_[loop].b = colors[col][2];			// Select Blue From Color Table
			}
			
			// If Number Pad 8 And Y Gravity Is Less Than 1.5 Increase Pull Upwards
			//if (keys[VK_NUMPAD8] && (particle[loop].yg<1.5f)) particle[loop].yg += 0.01f;

			// If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
			//if (keys[VK_NUMPAD2] && (particle[loop].yg>-1.5f)) particle[loop].yg -= 0.01f;

			// If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
			//if (keys[VK_NUMPAD6] && (particle[loop].xg<1.5f)) particle[loop].xg += 0.01f;

			// If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
			//if (keys[VK_NUMPAD4] && (particle[loop].xg>-1.5f)) particle[loop].xg -= 0.01f;

			//if (keys[VK_TAB])										// Tab Key Causes A Burst
			//{
			//	particle[loop].x = 0.0f;								// Center On X Axis
			//	particle[loop].y = 0.0f;								// Center On Y Axis
			//	particle[loop].z = 0.0f;								// Center On Z Axis
			//	particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;	// Random Speed On X Axis
			//	particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;	// Random Speed On Y Axis
			//	particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;	// Random Speed On Z Axis
			//}
		}
	}

/*
	//for (int loop = 0; loop < MAX_PARTICLES; loop++) // Loop Through All The Particles 
	//{
	//	if (particlesArray_[loop].active) // If The Particle Is Active 
	//	{
	//		float x = particlesArray_[loop].x; // Grab Our Particle X Position 
	//		float y = particlesArray_[loop].y; // Grab Our Particle Y Position 
	//		float z = particlesArray_[loop].z + zoom; // Particle Z Pos + Zoom // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life 
	//		glColor4f(particlesArray_[loop].r, particlesArray_[loop].g, particlesArray_[loop].b, particlesArray_[loop].life);
	//		
	//		glBegin(GL_TRIANGLE_STRIP); // Build Quad From A Triangle Strip glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right 
	//		glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left 
	//		glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right 
	//		glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left 
	//		glEnd(); // Done Building Triangle Strip 
	//		
	//		particlesArray_[loop].x += particlesArray_[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed 
	//		particlesArray_[loop].y += particlesArray_[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed 
	//		particlesArray_[loop].z += particlesArray_[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed 
	//		particlesArray_[loop].xi += particlesArray_[loop].xg; // Take Pull On X Axis Into Account 
	//		particlesArray_[loop].yi += particlesArray_[loop].yg; // Take Pull On Y Axis Into Account 
	//		particlesArray_[loop].zi += particlesArray_[loop].zg; // Take Pull On Z Axis Into Account 
	//		particlesArray_[loop].life -= particlesArray_[loop].fade; // Reduce Particles Life By 'Fade' 

	//		if (particlesArray_[loop].life < 0.0f) // If Particle Is Burned Out 
	//		{
	//			particlesArray_[loop].life = 1.0f; // Give It New Life 
	//			particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f; // Random Fade Value 
	//			//particlesArray_[loop].x = getSpaceShipX(); // Center On X Axis 
	//			particlesArray_[loop].y = 0.0f; // Center On Y Axis 
	//			particlesArray_[loop].z = 0.0f; // Center On Z Axis 
	//			particlesArray_[loop].xi = xspeed + float((rand() % 60) - 32.0f); // X Axis Speed And Direction 
	//			particlesArray_[loop].yi = yspeed + float((rand() % 60) - 30.0f); // Y Axis Speed And Direction 
	//			particlesArray_[loop].zi = float((rand() % 60) - 30.0f); // Z Axis Speed And Direction 
	//			particlesArray_[loop].r = colors[col][0]; // Select Red From Color Table 
	//			particlesArray_[loop].g = colors[col][1]; // Select Green From Color Table 
	//			particlesArray_[loop].b = colors[col][2]; // Select Blue From Color Table 
	//		}
	//	}
	//}

	*/




}

void ParticlesEngineClass::privateUpdate()
{
	col++;							// Change The Particle Color
	if (col>11)	col = 0;
}
