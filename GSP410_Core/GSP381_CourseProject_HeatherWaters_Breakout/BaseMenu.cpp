#include "BaseMenu.h"

BaseMenu::BaseMenu(void)
{
	// placeholder
	backgroundName = L"optionsbackground.png";
	menuItemSelected = 0;

	buttonSound = NULL;
	myInput = NULL;
}


BaseMenu::~BaseMenu(void)
{
}

bool BaseMenu::Init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device)
{
	myInput = input;
	mySounds = sounds;

	// load menu background
	background = new Surface();
	background->loadSurface(device, backgroundName);

	// load sound
	buttonSound = mySounds->loadFile("tick.mp3", 1);
	mySounds->hasPlayed = false;

	return true;
}

void BaseMenu::Update()
{
	myInput->getInput();

	// get menu movement input
	if(myInput->keyPress(DIK_UP))
	{
		mySounds->playSound(buttonSound);
		
		menuItemSelected --;
	}

	if ( myInput->keyPress(DIK_DOWN))
	{
		mySounds->playSound(buttonSound);
		
		menuItemSelected ++;
	}

	// get menu pressed input
	if (myInput->keyPress(DIK_RETURN))
	{
		MenuSelection();
		//mySounds->stopSound();
	}
}

void BaseMenu::Render(LPDIRECT3DDEVICE9 device)
{
	// render background
	background->render(device);

}

void BaseMenu::Shutdown()
{

}
