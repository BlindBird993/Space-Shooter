#pragma once

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter();

	double fps;

	void CalculateFrameRate();
};
