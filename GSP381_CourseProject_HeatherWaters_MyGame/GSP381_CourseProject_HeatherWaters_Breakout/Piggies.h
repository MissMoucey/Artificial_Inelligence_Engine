#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>

class Model;

class Piggies
{
public:
	Piggies(void);
	~Piggies(void);

	bool init(LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device);
	void update(float);

	void getPostionXYZ(float* x, float* y, float* z);
	void getWidthAndLength( float* width, float* length);

	float randNum(float lowest, float highest);

	bool alive;

private:
	Model* piggy;

	float positionX;
	float positionZ;

	float rotationY;
};