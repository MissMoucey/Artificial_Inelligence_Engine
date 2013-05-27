#pragma once

#include <d3d9.h>
#include <d3dx9tex.h>

struct SteeringOutput
{
	D3DXVECTOR3 linear;
	float		angular;
};

class Kinematic
{
private:
	D3DXVECTOR3 position;
	float		orientation;
	D3DXVECTOR3 velocity;
	float		rotation;

public:
	Kinematic(void);
	~Kinematic(void);

	void Update( SteeringOutput steering, int time);
	float GetNewOrientation();

};

