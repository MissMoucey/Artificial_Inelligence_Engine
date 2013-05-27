#include "Model.h"
#include "Piggies.h"
#include <ctime>

const float POSITIONY = -10.0f;
const float MAX_POSITIONX = 22.0f;
const float MIN_POSITIONX = -22.0f;
const float MAX_POSITIONZ = 45.0f; // 35.0f;
const float MIN_POSITIONZ = -5.0f;

const float WIDTH = 3.0f;
const float LENGTH = 5.0f;

Piggies::Piggies(void)
{
}

Piggies::~Piggies(void)
{
	if (piggy != NULL){delete piggy;}
}

bool Piggies::init(LPDIRECT3DDEVICE9 device)
{
	// TODO: randomize the spawn location.
	positionX = randNum(MIN_POSITIONX, MAX_POSITIONX);
	positionZ = randNum(MAX_POSITIONZ, 90);

	rotationY = 3.0f;

	piggy = new Model();
	// load piggy
	piggy->loadModel(device, L"Piggy.x");
	// set the scale of the model
	piggy->setScale(D3DXVECTOR3(0.015f, 0.015f, 0.015f));

	alive = true;

	return true;
}

void Piggies::render(LPDIRECT3DDEVICE9 device)
{
	if ( alive )
	{
		piggy->setPosition(D3DXVECTOR3(positionX, POSITIONY, positionZ));
		piggy->setRotation(D3DXVECTOR3(rotationY, 0, 0));
		piggy->render(device);
	}
}

void Piggies::update(float speed)
{
	// TODO: pathfindin
	//if ( )
		positionZ -= speed;

	////stop the piggies from going past the max and min positions
	//if ( positionX > MAX_POSITIONX)
	//	positionX = MAX_POSITIONX;
	//else if ( positionX < MIN_POSITIONX)
	//	positionX = MIN_POSITIONX;

	//if ( positionZ > MAX_POSITIONZ)
	//	positionZ = MAX_POSITIONZ;
	if ( positionZ < MIN_POSITIONZ)
	{
		positionZ = MAX_POSITIONZ;
		positionX = randNum(MIN_POSITIONX, MAX_POSITIONX);
	}

	if ( alive == false)
	{
		positionZ = MAX_POSITIONZ;
		alive = true;
		positionX = randNum(MIN_POSITIONX, MAX_POSITIONX);
	}
}

void Piggies::getPostionXYZ(float* x, float* y, float* z)
{
	*x = positionX;
	*y = POSITIONY;
	*z = positionZ;
}

float Piggies::randNum(float lowest, float highest )
{
	//srand((unsigned)time(0)); 
    int random_integer; 

	int range=(highest-lowest) + 1; 
    for(int index=0; index<10; index++)
        random_integer = lowest + int(range*rand()/(RAND_MAX + 1.0)); 
	return random_integer;
}

void Piggies::getWidthAndLength( float* width, float* length)
{
	*width = WIDTH;
	*length = LENGTH;
}