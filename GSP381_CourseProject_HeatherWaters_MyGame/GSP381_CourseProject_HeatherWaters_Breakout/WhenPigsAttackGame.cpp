#include "2dSurface.h"
#include "InputManager.h"
#include "WhenPigsAttackGame.h"
#include "Camera.h"
#include "lightManager.h"
#include "GirPlayer.h"

WhenPigsAttackGame::WhenPigsAttackGame(void)
{

}
WhenPigsAttackGame::~WhenPigsAttackGame(void)
{
	delete girPlayer;
}

bool WhenPigsAttackGame::init(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	myInput = input;

	// load gir
	girPlayer = new GirPlayer();
	girPlayer->init(input, device);

	//setup the camera
	camera = new Camera();
	cameraPos = D3DXVECTOR3(0.0, 0.0, 10.0);
	camera->create(device, 1.0f, 1000.f);
	camera->setLookAt(cameraPos);
	camera->setPosition(D3DXVECTOR3(0.0f,0.0f, -25.0f));

	//create lighting
	lights = new LightManager(device);
	int light_one = lights->createLight();
	lights->setPosition(light_one, D3DXVECTOR3(0.0f,20.0f,-25.0f));
	lights->setRange(light_one, 200.0f);

	return true;
}

void WhenPigsAttackGame::updateFrames(int numberOfFrames)
{
	// update gir
	girPlayer->update( numberOfFrames );

	// update the camera
	if ( myInput->keyPress(DIK_LEFT))
		camera->setLookAt(D3DXVECTOR3(cameraPos.x++, cameraPos.y, cameraPos.z));
	if ( myInput->keyPress(DIK_RIGHT))
		camera->setLookAt(D3DXVECTOR3(cameraPos.x--, cameraPos.y, cameraPos.z));
	if ( myInput->keyPress(DIK_UP))
		camera->setLookAt(D3DXVECTOR3(cameraPos.x, cameraPos.y++, cameraPos.z));
	if ( myInput->keyPress(DIK_DOWN))
		camera->setLookAt(D3DXVECTOR3(cameraPos.x, cameraPos.y--, cameraPos.z));
}

void WhenPigsAttackGame::render(LPDIRECT3DDEVICE9 device)
{
	// render gir - player
	girPlayer->render(device);
}