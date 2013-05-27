#include <d3dx9tex.h>
#include "dxMgr.h"

dxMgr::dxMgr(void)
{
	direct3d = NULL; //The Direct3D Object
 	direct3dDevice = NULL; //The Device object
}

dxMgr::~dxMgr(void)
{
	if( direct3dDevice != NULL) 
	{
        direct3dDevice->Release();
		direct3dDevice = NULL;
	}
    if( direct3d != NULL)
	{
        direct3d->Release();
		direct3d = NULL;
	}
}

bool dxMgr::init(HWND hwnd, int width, int height, bool fullscreen)
{
	HRESULT hr;
	direct3d = Direct3DCreate9( D3D_SDK_VERSION );
	if(direct3d == NULL)
	{
		return false;
	}

	bool windowed = true;
	if (fullscreen){
		windowed = false;
	}

	//Setup the present parameters
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = windowed; //Windowed or Fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //discards the previous frames
	d3dpp.BackBufferFormat = D3DFMT_R5G6B5; //The display format
	d3dpp.BackBufferCount  = 1;	//Number of back buffers
	d3dpp.BackBufferHeight = height; //height of the backbuffer
	d3dpp.BackBufferWidth  = width; //width of the backbuffer
	d3dpp.hDeviceWindow    = hwnd; //handle to our window
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //The stencil format
    d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


	//Create the Video Device
	hr = direct3d->CreateDevice( D3DADAPTER_DEFAULT, //The default adapter is the primary display adapter
							D3DDEVTYPE_HAL, //the HAL (hardware accelerated layer) uses your 3d accelerator card
							hwnd,
                            D3DCREATE_HARDWARE_VERTEXPROCESSING, //sets the graphic card to do the hardware vertexprocessing
                            &d3dpp, //The present parameters we created above
							&direct3dDevice 
							);
	if( FAILED(hr)){
        return false;
    }
	direct3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	direct3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	direct3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE); //this normalizes the normal values (this is important for how lighting effects your models)

	return true;
}

void dxMgr::beginRender()
{
	if( NULL == direct3dDevice )
        return;

    // Clear the backbuffer to a black color
    direct3dDevice->Clear( 0, //number of rectangles to clear, 0 for all
						NULL, //rects to be cleared, NULL for entire buffer
						D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, //the buffer to clear
						D3DCOLOR_XRGB(55,55,55), //the Color to fill the buffer with
						1.0f, //depth for the stencil buffer, (since we arent using it it doesnt matter)
						0 //stencil buffer clear
						);

	direct3dDevice->BeginScene();
}

void dxMgr::endRender(void)
{	
	direct3dDevice->EndScene();
    direct3dDevice->Present( NULL, NULL, NULL, NULL );
}

LPDIRECT3DDEVICE9 dxMgr::getD3DDevice()
{ 
	return direct3dDevice; 
}

void dxMgr::quickAndDrityViewSetup(){

	D3DXMATRIX viewMatrix; //the view matrix
	D3DXMATRIX projectionMatrix; // the projection matrix
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 30.0f); //the position of our camera
	D3DXVECTOR3 target = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //the lookat target of our camera

	float aspect = 1.333f; // the aspect ratio of the screen
	float nearClip = 1.0f; //nearest point at which the objects stop rendering 
	float farClip = 1000.0f; //farthest point at which the objects stop rendering 

	//Setup the Projection Matrix
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspect, nearClip, farClip);
    //Set the Projection
	direct3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	//Setup the View
	D3DXMatrixLookAtLH(&viewMatrix, 
						&position,		//camera's position
						&target,		//camera's target
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));// the up direction
	//Set the View
	direct3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
	
	//Turn on lighting
	direct3dDevice->SetRenderState(D3DRS_LIGHTING,   TRUE);

	//Create a new Light
	D3DLIGHT9 light;
    light.Type         = D3DLIGHT_POINT; //point light, lights in every direction.
    light.Diffuse.r    = light.Diffuse.g  = light.Diffuse.b  = 1.0f;
    light.Specular.r   = light.Specular.g = light.Specular.b = 0.0f;
    light.Ambient.r    = light.Ambient.g  = light.Ambient.b  = 0.3f;
    light.Position     = D3DXVECTOR3( 0.0f, 10.0f, 25.0f );
    light.Attenuation0 = light.Attenuation1 = light.Attenuation2 = 0.0f;
    light.Range        = 60.0f;

	//Set the light
    direct3dDevice->SetLight(0, &light );
	//Turn on the light
    direct3dDevice->LightEnable(0, TRUE );

}

void dxMgr::enableFullScreenMode(HWND hwnd, bool enable)
{
	// switch to full screen mode
	if( enable)
	{
		// are we already in full screen mode?
		if ( !d3dpp.Windowed)
			return;

		// get the current screen resolution
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
//600;//
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.Windowed = false;

		// change the window style to a more full screen friendly style
		SetWindowLongPtr( hwnd, GWL_STYLE, WS_POPUP);

		// call SetWindowPos for the change to take effect
		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height,
					SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	// switch to windowed mode
	else
	{
		// are we already in windowed mode?
		if ( d3dpp.Windowed)
			return;

		// default to a client rectangle of 800 x 600
		RECT R = {0, 0, 800, 600};
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferWidth = 800;
		d3dpp.BackBufferHeight = 600;
		d3dpp.Windowed = true;

		// change the window style to a more windowed friendly style
		SetWindowLongPtr( hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// call SetWindowPos
		SetWindowPos(hwnd, HWND_TOP, 100, 100,
			R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	// reset the device with the changes
	//onLostDevice();
	direct3dDevice->Reset(&d3dpp);
	//onResetDevice();
	
}