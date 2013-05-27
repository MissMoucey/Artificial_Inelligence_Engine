#include "GameState.h"

GameState::GameState(void)
{
}

GameState::~GameState(void)
{
	//delete the dxManager manager
	if( dxManager != NULL) 
	{
		delete dxManager;
		dxManager = NULL;
	}
}

bool GameState::Init(HWND wndHandle, HINSTANCE hInst) 
{
	activeState = MAINMENU;

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

	//Create the sound manager
	sound = new SoundManager();
	sound->init(wndHandle);

	//create a new Menu
	mainMenu = new MainMenu();
	mainMenu->Init(input, sound, dxManager->getD3DDevice());
	activeState = MAINMENU;

	// create a new options menu
	//optionsMenu = new OptionsMenu();
	//optionsMenu->init(input, sound, dxManager->getD3DDevice());


	//create a new frame timer
	timer = new FrameTimer();
	timer->init(60);

	// directShow
	//directShow = new DirectShow();
	//directShow->Initialize(wndHandle, input, fullscreen);
	//directShow->PlayVideo();
	//directShow->Release(wndHandle);

	//credits = new Credits();

	return true;
}

void GameState::Update(HWND hwnd)
{
	int framesToUpdate;
	//call our update function
	framesToUpdate = timer->framesToUpdate();

	//if ( directShow->isPlaying == false)
	//{
		//update the menu
		if (activeState == MAINMENU)
		{
			// Call the update to get the current gamestate
			mainMenu->Update();

			// if the user selects exit then quit the game
			if (mainMenu->GetMessage() == 3)
			{
				activeState = QUIT;
				PostQuitMessage(0);
				delete mainMenu;
			}
			// if the user selects NEW GAME then start a new game.
			else if (mainMenu->GetMessage() == 1)
			{
				//if an exiting game exists delete it

				//start a new game
				activeState = GAMESTART;
			}
			// if the user selects OPTIONS MENU then open that menu.
			else if (mainMenu->GetMessage() == 2)
			{
				//optionsMenu = new OptionsMenu();
				//optionsMenu->init(input, sound, dxManager->getD3DDevice());
				//activeState = OPTIONS;
			}
		}

		else if ( activeState == OPTIONS)
		{
			// call the options menu update function
			// if the user selects return the return to the main menu.
			// set the activeState to  MAINMENU and reactivate the menu
			// call the main menu init function
			//	......
		}

		else if ( activeState == GAMESTART)
		{
			// create a new game
		}



		// BEGIN RENDER
		dxManager->beginRender();

		// main menu render call
		if (activeState == MAINMENU)
		{
			mainMenu->Render(dxManager->getD3DDevice());
		}

		// game render call
		else if (activeState == GAMESTART)
		{
			
		}

		// options menu render call
		else if (activeState == OPTIONS)
		{
			
		}

		// END RENDER
		dxManager->endRender();

	//}
	//else if ( directShow->isPlaying == true)
	//{
		//// check to see if the video is still playing
		//directShow->StopVideo();
	//}

}