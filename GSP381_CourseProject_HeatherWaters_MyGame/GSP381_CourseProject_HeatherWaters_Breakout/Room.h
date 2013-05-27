#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>

class Model;

class Room
{
public:
	Room(void);
	~Room(void);

	bool init(LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device);
	void update();
	void getPostionXYZ(float* x, float* y, float* z);

private:
	Model* room;

	float positionX;
	float positionZ;
};