#include <d3d9.h>
#include <string>
#include <list>
#include <vector>

class Model;
class InputManger;

class Gun
{
public:
	Gun(void);
	~Gun(void);

	void init(InputManager* input, LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device);
	void update();
	void getPostionXYZ(float* x, float* z);
	void setPosition(float x, float z);

private:
	InputManager* myInput;
	Model* bullet;

	float positionX;
	float positionZ;
	int direction;
	int speed;
};

