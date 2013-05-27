#pragma once

#include "2dSurface.h"
#include "InputManager.h"
#include "SoundManager.h"

class BaseMenu
{
public:
	BaseMenu(void);
	~BaseMenu(void);

	bool Init(InputManager* input, SoundManager* sounds, LPDIRECT3DDEVICE9 device);
	void Update();
	void Render(LPDIRECT3DDEVICE9 device);
	virtual void MenuSelection() {NULL;};		// overriden in derrived classes
	void Shutdown();

	LPCWSTR backgroundName;

	InputManager* myInput;
	SoundManager* mySounds;
	Surface* background;

	int menuItemSelected;

private:
	int buttonSound;
	
};

