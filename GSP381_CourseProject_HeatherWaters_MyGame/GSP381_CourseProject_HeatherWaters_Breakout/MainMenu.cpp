#include "2dSurface.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "MainMenu.h"

MainMenu::MainMenu(){
	//null all the objects we will be useing
	myInput = NULL;
	background = NULL;
	newGame = NULL;
	newGameHighlighted = NULL;
	exit = NULL;
	exitHighlighted = NULL;
	options = NULL;
	optionsHighlighted = NULL;
	credits = NULL;
	creditsHighlighted = NULL;
	buttonSound = NULL;
}

MainMenu::~MainMenu(){
	//Delete everything we created for the menu;
	if (myInput != NULL){delete myInput;}
	if (background != NULL){delete background;}
	if (newGame != NULL){delete newGame;}
	if (newGameHighlighted != NULL){delete newGameHighlighted;}
	if (exit != NULL){delete exit;}
	if (exitHighlighted != NULL){delete exitHighlighted;}
	if (options != NULL){delete options;}
	if (optionsHighlighted != NULL){delete optionsHighlighted;}
	if (credits != NULL){delete credits;}
	if (creditsHighlighted != NULL){delete creditsHighlighted;}

}

bool MainMenu::init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device){
	myInput = input;
	mySounds = sounds;

	//0 is new game, 1 is exit;
	menuItemSelected = 1;
	message = 0;
	//load menu Images
	//load background menubackground.jpg
	background = new Surface();
	background->loadSurface(device, L"menuBackground600.png");
	
	//load new game image
	newGame = new Surface();
	newGame->loadSurface(device, L"newgame.png");
	newGame->setPosition(50,200);
	newGameHighlighted = new Surface();
	newGameHighlighted->loadSurface(device, L"newgameh.png");
	newGameHighlighted->setPosition(50,200);
	//load options image
	options = new Surface();
	options->loadSurface(device, L"options.png");
	options->setPosition(50,400);
	optionsHighlighted = new Surface();
	optionsHighlighted->loadSurface(device, L"optionsh.png");
	optionsHighlighted->setPosition(50,400);
	//load credits image
	credits = new Surface();
	credits->loadSurface(device, L"credits.png");
	credits->setPosition(500,200);
	creditsHighlighted = new Surface();
	creditsHighlighted->loadSurface(device, L"creditsh.png");
	creditsHighlighted->setPosition(500,200);
	//load exit image
	exit = new Surface();
	exit->loadSurface(device, L"exit.png");
	exit->setPosition(500,400);
	exitHighlighted = new Surface();
	exitHighlighted->loadSurface(device, L"exith.png");
	exitHighlighted->setPosition(500,400);

	// load sound
	buttonSound = mySounds->loadFile("tick.mp3", 1);
	mySounds->hasPlayed = false;

	return true;
}

void MainMenu::update(){
	myInput->getInput();

	mySounds->loopSound("OneBigVideoGame.mp3");

	//get menu movement input
	if (myInput->keyPress(DIK_UP))
	{
		mySounds->playSound(buttonSound);

		if (menuItemSelected == NEW_GAME){
			menuItemSelected = EXIT;
		} else if (menuItemSelected == OPTIONS){
			menuItemSelected = NEW_GAME;
		} else if (menuItemSelected == CREDITS){
			menuItemSelected = OPTIONS;
		} else if (menuItemSelected == EXIT){
			menuItemSelected = CREDITS;
		}
	}
	else if (myInput->keyPress(DIK_DOWN))
	{
		mySounds->playSound(buttonSound);

		if (menuItemSelected == NEW_GAME){
			menuItemSelected = OPTIONS;
		} else if (menuItemSelected == OPTIONS){
			menuItemSelected = CREDITS;
		} else if (menuItemSelected == CREDITS){
			menuItemSelected = EXIT;
		} else if (menuItemSelected == EXIT){
			menuItemSelected = NEW_GAME;
		}
	}

	//get menu pressed input
	if (myInput->keyPress(DIK_RETURN)){
		switch (menuItemSelected){
			case NEW_GAME: {message = NEW_GAME; break;}
			case OPTIONS: {message = OPTIONS; break;}
			case CREDITS: {message = CREDITS; break;}
			case EXIT: {message = EXIT; break;}
		}	
		mySounds->stopSound();
	}
}

void MainMenu::render(LPDIRECT3DDEVICE9 device){
	//render menu
	//render background
	background->render(device);
	
	//render menu items based on which is highlighted
	if (menuItemSelected == NEW_GAME){				// new game
		newGameHighlighted->render(device);
		options->render(device);
		credits->render(device);
		exit->render(device);
	} else if ( menuItemSelected == OPTIONS){		// options
		newGame->render(device);
		optionsHighlighted->render(device);
		credits->render(device);
		exit->render(device);
	} else if (menuItemSelected == CREDITS){		// exit
		newGame->render(device);
		options->render(device);
		creditsHighlighted->render(device);
		exit->render(device);
	} else if (menuItemSelected == EXIT){		// exit
		newGame->render(device);
		options->render(device);
		credits->render(device);
		exitHighlighted->render(device);
	}
	
}

int MainMenu::getMessage(){
	return message;
}