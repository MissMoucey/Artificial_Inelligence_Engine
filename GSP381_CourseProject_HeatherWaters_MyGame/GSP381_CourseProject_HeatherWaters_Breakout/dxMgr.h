#include <d3dx9tex.h>
#include <d3d9.h>


class dxMgr
{
public:
	dxMgr(void); //Constructor
	~dxMgr(void); //deconstructor

	bool init(HWND hwnd, int width, int height, bool fullscreen); //initializes our interface
	void beginRender(void); //starts the scene render
	void endRender(void); //ends the scene render and presents to the screen
	LPDIRECT3DDEVICE9 getD3DDevice(); //returns the device
	void quickAndDrityViewSetup();
	void enableFullScreenMode(HWND hwnd, bool enable);

private:

	LPDIRECT3D9             direct3d; //This is the Direct3D object
	LPDIRECT3DDEVICE9       direct3dDevice; //This is our device object
	D3DPRESENT_PARAMETERS	d3dpp; 
};