#pragma once

class FrameTimer
{
public:
	FrameTimer(void);
	~FrameTimer(void);

	void init(int fps);
	int framesToUpdate();

private:
	
	// timer variables
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	LARGE_INTEGER timerFreq;

	float fps;
	float intervals;
	float intervalsSinceLastUpdate;
	float framesInLastSecond;
	float intervalsPerFrame;
	int Requested_FPS;

};