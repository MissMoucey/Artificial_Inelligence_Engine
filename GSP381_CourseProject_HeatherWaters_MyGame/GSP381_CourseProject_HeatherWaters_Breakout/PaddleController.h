#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>

class Model;
class InputManager;

class PaddleController{
public:
	PaddleController();
	~PaddleController();
	
	bool init(InputManager* input, LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device);
	void update();
	void getPaddleXY(float* x, float* y);
	float getWidth();

private:
	InputManager* myInput;
	Model* paddle;
	float paddleX;

};