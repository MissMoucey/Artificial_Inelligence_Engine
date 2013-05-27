#pragma once

class InputManager;
class Surface;
class Level;
class Camera;
class LightManager;
class GirPlayer;
class Piggies;
class Room;

class WhenPigsAttackGame
{
public:
	WhenPigsAttackGame(void);
	~WhenPigsAttackGame(void);

	bool init(InputManager* input, LPDIRECT3DDEVICE9 device);
	void updateFrames(int numberOfFrames);
	void render(LPDIRECT3DDEVICE9 device);
	int getMessage();
	enum{NO_MESSAGE=0, GAME_OVER= 1, QUIT = 2, GAMEOVER = 3};

private:
	InputManager*	myInput;
	Camera*			camera;
	LightManager*	lights;
	GirPlayer*		girPlayer;

	D3DXVECTOR3		cameraPos;
};

