#include <windows.h>
#include "GameMain.h"

HINSTANCE hInst;				// holds the instance for this app
HWND wndHandle;					// global window handle

bool    initWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Link in the DirectX libraries required to compile
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// call our function to init and create our window
	if (!initWindow(hInstance))
	{
		MessageBox(NULL, L"Unable to create window", L"ERROR", MB_OK);
		return false;
	}

	// Create the game main
	GameMain *game = new GameMain();

	// Initialize the game object
	if( game->init(wndHandle, hInstance) == false) 
			return 0;

	// Main message loop:
	// Enter the message loop
    MSG msg; 
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		// check for messages
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		// if there are no messages waiting update the game
		else
		{
			game->update(wndHandle);
		}
    }

	// Delete the game object
	if (game){
		delete game;
	}

	return (int) msg.wParam;
}

bool initWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"When Pigs Attack";
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	ULONG window_width=800;
    ULONG window_height=600;

	DWORD style=WS_POPUP|WS_VISIBLE;

	style =  WS_OVERLAPPEDWINDOW;

	wndHandle = CreateWindow(L"When Pigs Attack", 
							 L"When Pigs Attack", 
							 style,
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 window_width, 
							 window_height, 
							 NULL, 
							 NULL, 
							 hInstance, 
							 NULL);
	if (!wndHandle){
      return false;
	}
 
   // Set the global instance handle
   hInst = hInstance;

   ShowWindow(wndHandle, SW_SHOW);
   UpdateWindow(wndHandle);

   return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}