#include "..\include\FPSCounter.h"
#include <windows.h> 
#include <mmsystem.h>
#pragma once

FPSCounter::FPSCounter()
{
	this->fps_ = 0;
	startTime_ = GetTickCount() * 0.001f;
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;    // FPS
	static float lastTime = 0.0f;           // It stores the time elapsed since the last frame
	static char strFrameRate[50] = { 0 };   // Output string
											// Here we get the current tick count and multiply it by 0.001 to convert from milliseconds to seconds.
	currentTime_ = GetTickCount() * 0.001f;

	// Increase the frame counter
	++framesPerSecond;

	// Now we subtract the last time from the current time. If the result is greater than one.
	// This means that the second has passed and you need to bring out a new FPS.
	if (currentTime_ - lastTime > 1.0f)
	{
		// Set lastTime at the current time. Now it will be used as the previous time for the next second.
		lastTime = currentTime_;

		// Install FPS for output.
		this->fps_ = framesPerSecond;

		// Reset the FPS.
		framesPerSecond = 0;
	}
}

float FPSCounter::getCurrentTime()
{
	return currentTime_ - startTime_;
}

float FPSCounter::getFpsValue()
{
	return fps_;
}
