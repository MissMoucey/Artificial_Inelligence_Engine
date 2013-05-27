#include "GameMain.h"
#include "dxMgr.h"
#include "dxText.h"
#include "2dSurface.h"
#include "Model.h"
#include "lightManager.h"
#include "Camera.h"
#include "FrameTimer.h"
#include "InputManager.h"
#include "DirectShow.h"
#include "MainMenu.h"
#include "optionsMenu.h"
#include "GameOverMenu.h"
#include "Credits.h"
#include "WhenPigsAttackGame.h"

GameMain::GameMain(void)
{
	wpaGame = NULL;
}

GameMain::~GameMain(void)
{
	//delete the dxManager manager
	if( dxManager != NULL) 
	{
		delete dxManager;
		dxManager = NULL;
	}
}

bool GameMain::init(HWND wndHandle, HINSTANCE hInst) 
{
	fullscreen = false;

	dxManager = new dxMgr(); //create our direct Manager
	dxManager->init(wndHandle, 800, 600, fullscreen); //Initialize our DirectX Manager
	if (!dxManager)
	{
		return false;
	}

	//Create a new InputManager
	input = new InputManager();
	input->init(hInst, wndHandle);

	//create a new frame timer
	timer = new FrameTimer();
	timer->init(60);

	//start a new game
	wpaGame = new WhenPigsAttackGame();
	wpaGame->init(input, dxManager->getD3DDevice());

	return true;
}

void GameMain::update(HWND hwnd)
{
	int framesToUpdate;
	//call our update function
	framesToUpdate = timer->framesToUpdate();

	wpaGame->updateFrames(framesToUpdate);

	if ( input->keyPress(DIK_ESCAPE))
	{
		active = NULL;
		PostQuitMessage(0);
		delete wpaGame;
	}

	// begin rendering
	dxManager->beginRender();

	wpaGame->render(dxManager->getD3DDevice());

	//end render
	dxManager->endRender();
}