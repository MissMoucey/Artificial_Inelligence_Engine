#include "2dSurface.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(void)
{
	myInput = NULL;
	background = NULL;
	fullscreenOn = NULL;
	fullscreenOff = NULL;
	fullscreenOnHighlighted = NULL;
	fullscreenOffHighlighted = NULL;
	returnToMain = NULL;
	returnHighlighted = NULL;
	buttonSound = NULL;
}


OptionsMenu::~OptionsMenu(void)
{
	if (myInput != NULL){delete myInput;}
	if (background != NULL){delete background;}
	if (fullscreenOn != NULL){delete fullscreenOn;}
	if (fullscreenOff != NULL){delete fullscreenOff;}
	if (fullscreenOnHighlighted != NULL){delete fullscreenOnHighlighted;}
	if (fullscreenOffHighlighted != NULL){delete fullscreenOffHighlighted;}
	if (returnToMain != NULL){delete returnToMain;}
	if (returnHighlighted != NULL){delete returnHighlighted;}
}

bool OptionsMenu::init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device){
	myInput = input;
	mySounds = sounds;

	menuItemSelected = FULLSCREEN;
	message = 0;

	// load background image
	background = new Surface();
	background->loadSurface(device, L"optionsbackground.png");

	//load fullscreen image
	fullscreenOn = new Surface();
	fullscreenOn->loadSurface(device, L"fullscreenon.png");
	fullscreenOn->setPosition(5,150);

	fullscreenOnHighlighted = new Surface();
	fullscreenOnHighlighted->loadSurface(device, L"fullscreenonh.png");
	fullscreenOnHighlighted->setPosition(5,150);

	fullscreenOff = new Surface();
	fullscreenOff->loadSurface(device, L"fullscreenoff.png");
	fullscreenOff->setPosition(5,150);

	fullscreenOffHighlighted = new Surface();
	fullscreenOffHighlighted->loadSurface(device, L"fullscreenoffh.png");
	fullscreenOffHighlighted->setPosition(5,150);

	// load return to menu image
	returnToMain = new Surface();
	returnToMain->loadSurface(device, L"exitOptions.png");
	returnToMain->setPosition(5,300);

	returnHighlighted = new Surface();
	returnHighlighted->loadSurface(device, L"exitOptionsh.png");
	returnHighlighted->setPosition(5,300);

	buttonSound = mySounds->loadFile("tick.mp3", 1);

	fullscreen = true;

	mySounds->hasPlayed = false;

	return true;
}

void OptionsMenu::update(){
	myInput->getInput();

	mySounds->loopSound("GearFight.mp3");

	if (myInput->keyPress(DIK_UP)){
		mySounds->playSound(buttonSound);

		if ( menuItemSelected == FULLSCREEN){
			menuItemSelected = RETURN;
		}
		else{
			menuItemSelected = FULLSCREEN;
		}
	}else if (myInput->keyPress(DIK_DOWN)){
		mySounds->playSound(buttonSound);

		if ( menuItemSelected == FULLSCREEN){
			menuItemSelected = RETURN;
		}
		else{
			menuItemSelected = FULLSCREEN;
		}
	}

	if ( myInput->keyPress(DIK_RETURN)){
		switch (menuItemSelected){
		case FULLSCREEN: { message = FULLSCREEN;
			if (fullscreen == true)
				fullscreen = false;
			else
				fullscreen = true;
			break;}
		case RETURN: {message = RETURN; break;}
		}
		mySounds->stopSound();
	}
}

void OptionsMenu::render(LPDIRECT3DDEVICE9 device){
	background->render(device);

	if ( menuItemSelected == FULLSCREEN)
	{
		if (fullscreen == false)
			fullscreenOffHighlighted->render(device);
		else if ( fullscreen == true )
			fullscreenOnHighlighted->render(device);
		returnToMain->render(device);
	}
	else
	{
		if (fullscreen == false)
			fullscreenOff->render(device);
		else if ( fullscreen == true)
			fullscreenOn->render(device);
		returnHighlighted->render(device);
	}
}

int OptionsMenu::getMessage()
{
	return message;
}