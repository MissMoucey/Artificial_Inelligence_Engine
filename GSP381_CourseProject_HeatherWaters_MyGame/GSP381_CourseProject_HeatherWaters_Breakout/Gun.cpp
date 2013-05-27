#include "inputmanager.h"
#include "Model.h"
#include "Gun.h"

const float POSITIONY = 5.0f;

Gun::Gun(void)
{
}

Gun::~Gun(void)
{
	if ( bullet != NULL){delete bullet;}
}

void Gun::init(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	myInput = input;

	positionX = 0;
	positionZ = 0;

	bullet = new Model();
	// load GIR
	bullet->loadModel(device, L"ball.x");
	// set the scale of the model
	bullet->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
}

void Gun::render(LPDIRECT3DDEVICE9 device)
{
	bullet->setPosition(D3DXVECTOR3(positionX, POSITIONY, positionZ));
	
	bullet->render(device);
}

void Gun::update()
{
	positionZ += 1.0f;
}

void Gun::getPostionXYZ(float* x, float* z)
{
	*x = positionX;
	*z = positionZ;
}

void Gun::setPosition(float x, float z)
{
	positionX = x;
	positionZ = z;
}
