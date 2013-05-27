#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
}


bool SoundManager::init(HWND wndHandle)
{

	hasPlayed = false;
	/*
	Create a System object and initialize.
	*/
	result = FMOD::System_Create(&system);
	if (FAILED(result))
		MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
	result = system->getVersion(&version);
	if (FAILED(result))
		MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
	if (version < FMOD_VERSION)
	{
		MessageBox(0, TEXT("Error! You are using an old version of FMOD %08x. This program requires %08x\n"),
			(LPCWSTR)version, FMOD_VERSION);
	}
	result = system->getNumDrivers(&numdrivers);
	if (FAILED(result))
		MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
	}
	else
	{
		result = system->getDriverCaps(0, &caps, 0, &speakermode);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		/*
		Set the user selected speaker mode.
		*/
		result = system->setSpeakerMode(speakermode);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			/*
			The user has the 'Acceleration' slider set to off! This is really bad
			for latency! You might want to warn the user about this.
			*/
			result = system->setDSPBufferSize(1024, 10);
			if (FAILED(result))
				MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		}
		result = system->getDriverInfo(0, name, 256, 0);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		if (strstr(name, "SigmaTel"))
		{
			/*
			Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
			PCM floating point output seems to solve it.
			*/
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,
				FMOD_DSP_RESAMPLER_LINEAR);
			if (FAILED(result))
				MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		}
	}
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		/*
		Ok, the speaker mode selected isn't supported by this soundcard. Switch it
		back to stereo...
		*/
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		/*
		... and re-init.
		*/
		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	if (FAILED(result))
		MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);

	return true;
}

int SoundManager::loadFile(char* filename, int bufferNumber)
{
	system->createSound(filename, FMOD_DEFAULT, 0, &sound[bufferNumber]);
	return bufferNumber;
}

void SoundManager::playSound(int bufferNumber)
{
	result = system->playSound(FMOD_CHANNEL_FREE, sound[bufferNumber], false, &channel); 
	if (FAILED(result))
		MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
}

void SoundManager::loopSound(char* fileName)
{
	if (hasPlayed == false)
	{
		result = system->createStream(fileName, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &myStream);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		result = system->playSound(FMOD_CHANNEL_FREE, myStream, true, &myChannel);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);

		// set the volume while it is paused
		result = myChannel->setVolume(0.5f);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);

		// this is where the sound really starts
		result = myChannel->setPaused(false);
		if (FAILED(result))
			MessageBox(0, TEXT("Error"), TEXT("ERROR"), MB_OK);
		hasPlayed = true;
	}
}

void SoundManager::stopSound()
{
	myChannel->setPaused(true);
}
