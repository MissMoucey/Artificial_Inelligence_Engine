#include "2dSurface.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "GameOverMenu.h"
#include "GirPlayer.h"
#include "dxText.h"

GameOverMenu::GameOverMenu(void)
{
	myInput = NULL;
	background = NULL;
	tryAgain = NULL;
	tryAgainHighlighted = NULL;
	giveUp = NULL;
	giveUpHighlighted = NULL;
	buttonSound = NULL;
}


GameOverMenu::~GameOverMenu(void)
{
	if (myInput != NULL){delete myInput;}
	if (background != NULL){delete background;}
	if (tryAgain != NULL){delete tryAgain;}
	if (tryAgainHighlighted != NULL){delete tryAgainHighlighted;}
	if (giveUp != NULL){delete giveUp;}
	if (giveUpHighlighted != NULL){delete giveUpHighlighted;}
}

bool GameOverMenu::init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device){
	myInput = input;
	mySounds = sounds;

	menuItemSelected = TRYAGAIN;
	message = 0;

	// load background image
	background = new Surface();
	background->loadSurface(device, L"gameOverGir.png");

	//load fullscreen image
	tryAgain = new Surface();
	tryAgain->loadSurface(device, L"tryAgain.png");
	tryAgain->setPosition(200,150);

	tryAgainHighlighted = new Surface();
	tryAgainHighlighted->loadSurface(device, L"tryAgainh.png");
	tryAgainHighlighted->setPosition(200,150);

	// load return to menu image
	giveUp = new Surface();
	giveUp->loadSurface(device, L"giveUp.png");
	giveUp->setPosition(200,300);

	giveUpHighlighted = new Surface();
	giveUpHighlighted->loadSurface(device, L"giveUph.png");
	giveUpHighlighted->setPosition(200,300);

	buttonSound = mySounds->loadFile("tick.mp3", 1);

	fullscreen = false;

	mySounds->hasPlayed = false;

	text = new dxText();
	text->init(25, device);

	gir = new GirPlayer();

	return true;
}

void GameOverMenu::update(){
	myInput->getInput();

	mySounds->loopSound("Ghosts.mp3");

	if (myInput->keyPress(DIK_UP)){
		mySounds->playSound(buttonSound);

		if ( menuItemSelected == TRYAGAIN){
			menuItemSelected = GIVEUP;
		}
		else{
			menuItemSelected = TRYAGAIN;
		}
	}else if (myInput->keyPress(DIK_DOWN)){
		mySounds->playSound(buttonSound);

		if ( menuItemSelected == TRYAGAIN){
			menuItemSelected = GIVEUP;
		}
		else{
			menuItemSelected = TRYAGAIN;
		}
	}

	if ( myInput->keyPress(DIK_RETURN))
	{
		switch (menuItemSelected)
		{
			case TRYAGAIN: { message = TRYAGAIN; break;}
			case GIVEUP: {message = GIVEUP; break;}
		}
		mySounds->stopSound();
	}
}

void GameOverMenu::render(LPDIRECT3DDEVICE9 device, int numOfEnemiesKilled){
	background->render(device);

	if ( menuItemSelected == TRYAGAIN)
	{
		tryAgainHighlighted->render(device);
		giveUp->render(device);
	}
	else
	{
		tryAgain->render(device);
		giveUpHighlighted->render(device);
	}

         char textOut[50] = "";
		 sprintf_s(textOut,"%d piggies were slaughtered!", numOfEnemiesKilled);
		 int a = lstrlenA(textOut);
		 BSTR unicodestr = SysAllocStringLen(NULL, a);
		 MultiByteToWideChar(CP_ACP, 0, textOut, a, unicodestr, a);
         text->drawText(unicodestr, 100, 450, 400, 600);
}

int GameOverMenu::getMessage()
{
	return message;
}