#pragma once

#include "BaseMenu.h"

class MainMenu : public BaseMenu
{
public:
	enum MAINMENUSTATE { NEW_GAME = 1, OPTIONS = 2, EXIT = 3 };

	MainMenu();
	~MainMenu();

	virtual void MenuSelection();

	int GetMessage();
	void SetMessage(MAINMENUSTATE message);

private:
	int menuItemSelected;
	MAINMENUSTATE choice;
};
