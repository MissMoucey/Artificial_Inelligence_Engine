#pragma once

class InputManager;
class Surface;
class SoundManager;

class OptionsMenu
{
public:
	OptionsMenu();
	~OptionsMenu();

	bool init(InputManager* input,  SoundManager* sounds, LPDIRECT3DDEVICE9 device);
	void update();
	void render(LPDIRECT3DDEVICE9 device);
	bool fullscreen;
	int getMessage();

	enum {NO_MESSAGE = 0, FULLSCREEN = 1, RETURN = 2};

private:
	InputManager* myInput;
	SoundManager* mySounds;
	Surface* background;
	Surface* fullscreenOn;
	Surface* fullscreenOnHighlighted;
	Surface* fullscreenOff;
	Surface* fullscreenOffHighlighted;
	Surface* returnToMain;
	Surface* returnHighlighted;

	int buttonSound;

	int menuItemSelected;
	int message;

};

