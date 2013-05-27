#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <list>
#include <vector>
#include "Kinematic.h"

class Model;
class InputManger;
class dxText;


class GirPlayer
{
public:
	GirPlayer(void);
	~GirPlayer(void);

	bool init(InputManager* input, LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device);
	void update( int time );
	void getPostionXYZ(float* x, float* y, float* z);
	void CheckCollision();

private:
	InputManager* myInput;
	Model* gir;

	//float positionX;
	//float positionZ;

	D3DXVECTOR3 position;
	float		orientation;

	float rotationY;
};

