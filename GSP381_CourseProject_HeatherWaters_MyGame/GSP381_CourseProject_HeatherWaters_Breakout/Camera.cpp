#include "Camera.h"


Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

bool Camera::create(LPDIRECT3DDEVICE9 device, float nearView, float farView)
{
	myDevice = device;
	nearClip = nearView;//nearest point at which the objects stop rendering 
	farClip = farView;//farthest point at which the objects stop rendering

	//the position of our camera
	position.x = 0.0;
	position.y = 0.0f;
	position.z = 0.0f;

	//the lookat target of our camera
	target.x = 0.0f;
	target.y = 0.0f;
	target.z = 0.0f;

	float aspect = 1.333f; // the aspect ratio of the screen

	//Setup the Projection Matrix
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspect, nearClip, farClip);
    //Set the Projection
	myDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	return true;
}
		
void Camera::setPosition(D3DXVECTOR3 newPosition)
{
	position = newPosition;
	resetView();
}

void Camera::setLookAt(D3DXVECTOR3 newTarget)
{
	target = newTarget;	
	resetView();
} 

void Camera::resetView(){
	//Setup the View
	D3DXMatrixLookAtLH(&viewMatrix, 
						&position,		//camera's position
						&target,		//camera's target
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));// the up direction
	//Set the View
	myDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}


