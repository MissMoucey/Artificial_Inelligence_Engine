#pragma once

class InputManager;
class Surface;
class SoundManager;

class MainMenu{
public:

	MainMenu();
	~MainMenu();

	bool init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device);
	void update();
	void render(LPDIRECT3DDEVICE9 device);
	int getMessage();
	//Message Enumerations
	enum { NEW_GAME = 1, OPTIONS = 2, CREDITS = 3, EXIT = 4 };

private:
	InputManager* myInput;
	SoundManager* mySounds;
	Surface* background;
	Surface* newGame;
	Surface* newGameHighlighted;
	Surface* exit;
	Surface* exitHighlighted;
	Surface* options;
	Surface* optionsHighlighted;
	Surface* credits;
	Surface* creditsHighlighted;

	int buttonSound;

	int menuItemSelected;
	int message;
};
