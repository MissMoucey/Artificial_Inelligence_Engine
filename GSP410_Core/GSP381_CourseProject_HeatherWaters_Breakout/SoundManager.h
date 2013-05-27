#pragma once
#include <dsound.h>
#include <string>
#include "dsutil.h"
#include <vector>
#include <fmod.hpp>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	bool init(HWND wndHandle);
	int loadFile(char* filename, int bufferNumber);
	void playSound(int bufferNumber);
	void loopSound(char* fileName);
	void stopSound();

	bool hasPlayed;

private:
	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Sound* sound[10];
	FMOD::Channel* channel;
	unsigned int version;
	int numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS caps;
	char name[256];
	bool m_bKeyDown[256];
	FMOD::Sound* myStream;
	FMOD::Channel* myChannel;

	int bufferNumber;

};