#include "Kinematic.h"


Kinematic::Kinematic(void)
{
}


Kinematic::~Kinematic(void)
{
}

void Kinematic::Update( SteeringOutput steering, int time)
{
	// update the position and orientation
	position += velocity * time;
	orientation += rotation * time;

	// and the velocity and rotation
	velocity += steering.linear * time;
	rotation += steering.angular * time;
}

float Kinematic::GetNewOrientation()
{
	// make sure that we have a velocity
	float length = sqrt( (velocity.x * velocity.x) + (velocity.y * velocity.y) + ( velocity.z * velocity.z));
	if (length > 0)
	{
		// calculate orientation using an arc tangent of the velocity components
		return atan2( -velocity.x, velocity.z);
	}

	else
		return orientation;
}