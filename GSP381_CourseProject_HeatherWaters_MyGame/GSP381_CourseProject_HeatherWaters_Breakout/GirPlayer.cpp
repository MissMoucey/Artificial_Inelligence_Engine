#include "InputManager.h"
#include "Model.h"
#include "GirPlayer.h"
#include "dxText.h"

const float POSITIONY = -10.0f;
const float MAX_POSITIONX = 22.0f;
const float MIN_POSITIONX = -22.0f;
const float MAX_POSITIONZ = 35.0f;
const float MIN_POSITIONZ = -5.0f;
//const float POSITIONZ = -0.0f;

GirPlayer::GirPlayer(void)
{
	gir = NULL;
}

GirPlayer::~GirPlayer(void)
{
	if ( gir != NULL){delete gir;}
}

bool GirPlayer::init(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	//Local pointer to the input manager
	myInput = input;

	position.x = 0.0f;
	//position.z = 0.0f;

	//rotationY = 1.5f;
	rotationY = 4.5f;

	gir = new Model();
	// load GIR
	gir->loadModel(device, L"GirRobot.x");
	// set the scale of the model
	gir->setScale(D3DXVECTOR3(0.010f, 0.010f, 0.010f));

	return true;
}

void GirPlayer::render(LPDIRECT3DDEVICE9 device)
{
	gir->setPosition(D3DXVECTOR3(position.x, POSITIONY, position.z));
	gir->setRotation(D3DXVECTOR3(rotationY, 0, 0));
	gir->render(device);
}

void GirPlayer::update( int time )
{
	myInput->getInput();
	
	 //move with WASD
	if ( myInput->keyDown(DIK_W))
	{
		position.z += 0.5f;
		rotationY = 4.5f;
	}
	else if ( myInput->keyDown(DIK_S))
	{
		position.z -= 0.5f;
		rotationY = 1.5f;
	}
	else if ( myInput->keyDown(DIK_A))
	{
		position.x -= 0.5f;
		rotationY = 3.0f;
	}
	else if ( myInput->keyDown(DIK_D))
	{
		position.x += 0.5f;
		rotationY = 0.0f;
	}

	//stop the player from going past the max and min positions
	if ( position.x > MAX_POSITIONX)
		position.x = MAX_POSITIONX;
	else if ( position.x < MIN_POSITIONX)
		position.x = MIN_POSITIONX;

	if ( position.z > MAX_POSITIONZ)
		position.z = MAX_POSITIONZ;
	else if ( position.z < MIN_POSITIONZ)
		position.z = MIN_POSITIONZ;
}

void GirPlayer::getPostionXYZ(float* x, float* y, float* z)
{
	*x = position.x;
	*y = POSITIONY;
	*z = position.z;
}

void GirPlayer::CheckCollision()
{
	
}