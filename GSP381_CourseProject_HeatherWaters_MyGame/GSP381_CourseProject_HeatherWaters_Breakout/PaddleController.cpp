#include "paddleController.h"
#include "model.h"
#include "inputmanager.h"

const float PADDLEY = -15.0f;
const float PADDLE_MAX_X = 20;
const float PADDLE_MIN_X = -20;
const float PADDLE_WIDTH = 3.0f;

PaddleController::PaddleController(){
	paddle = NULL;
}

PaddleController::~PaddleController(){
	if (paddle != NULL){delete paddle;}
}

bool PaddleController::init(InputManager* input, LPDIRECT3DDEVICE9 device){
	//Local pointer to the input manager
	myInput = input;
	//set the paddle to start at 0
	paddleX = 0;

	paddle = new Model();
	//load the paddle
	paddle->loadModel(device, L"paddle.x");
	//set the scale of the model
	paddle->setScale(D3DXVECTOR3(0.25f,0.25f,0.25f));

	return true;
}

void PaddleController::render(LPDIRECT3DDEVICE9 device){
	paddle->setPosition(D3DXVECTOR3(paddleX,PADDLEY, 0.0f));
	paddle->render(device);
}

void PaddleController::update(){
	myInput->getInput();

	//updates the paddleX
	paddleX+= myInput->getMouseMovingX()/10;

	//stop the paddle from going past the Max and Min paddle positions
	if (paddleX > PADDLE_MAX_X){
		paddleX = PADDLE_MAX_X;
	} else if (paddleX < PADDLE_MIN_X){
		paddleX = PADDLE_MIN_X;
	}
}

void PaddleController::getPaddleXY(float* x, float* y){
	*x = paddleX;
	*y = PADDLEY;
}

float PaddleController::getWidth(){
	return PADDLE_WIDTH;
}