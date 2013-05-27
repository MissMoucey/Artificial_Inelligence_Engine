#include "MainMenu.h"

MainMenu::MainMenu()
{
	backgroundName = L"optionsbackground.png";
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::MenuSelection()
{
	
	switch (menuItemSelected)
	{
	// NEW GAME
	case 1:
		{
			choice = NEW_GAME;
			break;
		}
	// OPTIONS
	case 2:
		{
			choice = OPTIONS;
			break;
		}
	// EXIT
	case 3:
		{
			choice = EXIT;
			break;
		}
	}
}

int MainMenu::GetMessage()
{
	return choice;
}

void MainMenu::SetMessage( MAINMENUSTATE message)
{
	choice = message;
}