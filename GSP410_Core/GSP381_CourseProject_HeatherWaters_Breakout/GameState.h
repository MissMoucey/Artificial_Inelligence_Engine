#pragma once

#include <windows.h>

//#include "DirectShow.h"
#include "MainMenu.h"
//#include "optionsMenu.h"
//#include "PauseMenu.h"
#include "Credits.h"
#include "dxMgr.h"
#include "FrameTimer.h"


class GameState
{
public:
	GameState(void);
	~GameState(void);

	bool Init(HWND wndHandle,HINSTANCE hInst);
	void Update(HWND hwnd);

	enum ACTIVESTATE {QUIT = 0, INTRO = 1, MAINMENU = 2, OPTIONS = 3, GAMESTART = 4, } activeState;

private:

	dxMgr*					dxManager;
	FrameTimer*				timer;
	InputManager*			input;
	SoundManager*			sound;
	MainMenu*				mainMenu;
	//OptionsMenu*			optionsMenu;
	//PauseMenu*			pauseMenu;
	//DirectShow*				directShow;
	Credits*				credits;

	bool					fullscreen;

};
