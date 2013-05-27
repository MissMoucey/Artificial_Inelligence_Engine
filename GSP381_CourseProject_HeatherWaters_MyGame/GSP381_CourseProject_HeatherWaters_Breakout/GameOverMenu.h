#pragma once

#include <d3dx9tex.h>
#include <string>
#include <list>

class InputManager;
class Surface;
class SoundManager;
class GirPlayer;
class dxText;

class GameOverMenu
{
public:
	GameOverMenu();
	~GameOverMenu();

	bool init(InputManager* input,  SoundManager* sounds, LPDIRECT3DDEVICE9 device);
	void update();
	void render(LPDIRECT3DDEVICE9 device, int numOfEnemiesKilled);
	bool fullscreen;
	int getMessage();

	enum {NO_MESSAGE = 0, TRYAGAIN = 1, GIVEUP = 2};

private:
	InputManager* myInput;
	SoundManager* mySounds;
	Surface* background;
	Surface* tryAgain;
	Surface* tryAgainHighlighted;
	Surface* giveUp;
	Surface* giveUpHighlighted;
	GirPlayer* gir;

	int buttonSound;

	int menuItemSelected;
	int message;

	dxText*	text;

};
