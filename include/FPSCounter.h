#pragma once

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter();
	void CalculateFrameRate();
	float getCurrentTime();
	float getFpsValue();
	double fps_;
private:
	float currentTime_;
	float startTime_;


};
