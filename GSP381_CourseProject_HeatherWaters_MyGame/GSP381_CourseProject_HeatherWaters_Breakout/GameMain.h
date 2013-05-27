#pragma once

#include <windows.h>

class dxMgr;
class Surface;
class Model;
class LightManager;
class Camera;
class FrameTimer;
class InputManager;
class WhenPigsAttackGame;
class Credits;

class GameMain
{
public:
	GameMain(void);
	~GameMain(void);

	bool init(HWND wndHandle,HINSTANCE hInst);
	void update(HWND hwnd);
	void render();
	enum {MENU = 1, GAME = 2, OPTIONS = 3, CREDITS = 4, GAME_OVER = 5 };

private:

	dxMgr*					dxManager;
	FrameTimer*				timer;
	InputManager*			input;
	WhenPigsAttackGame*		wpaGame;
	Credits*				credits;

	bool					fullscreen;
	int						active;

	int						numOfEnemiesKilled;

};
