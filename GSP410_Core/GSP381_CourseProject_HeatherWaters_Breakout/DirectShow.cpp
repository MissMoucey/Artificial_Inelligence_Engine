//#include "DirectShow.h"
//#include <DShow.h>
//#include "InputManager.h"
//
//DirectShow::DirectShow(void)
//{
//	thisInput = NULL;
//}
//
//
//DirectShow::~DirectShow(void)
//{
//	if (thisInput != NULL){delete thisInput;}
//}
//
//void DirectShow::Initialize(HWND hwnd, InputManager* input, bool fullscreen)
//{
//	thisInput = input;
//
//	isPlaying = true;
//	CoInitialize(NULL);
//	CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
//	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pControl);
//	m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_pEvent);
//	m_pGraphBuilder->RenderFile(L"WhenPigsAttackIntro.wmv", NULL);
//
//	// video window
//	m_pControl->QueryInterface(IID_IVideoWindow, (void**)&m_pVideoWindow);
//
//	// set up the window
//	m_pVideoWindow->put_Owner((OAHWND)hwnd);
//
//	// set the style
//	m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);
//
//	// obtain the size of the window
//	RECT WinRect;
//	GetClientRect(hwnd, &WinRect);
//
//	// set the video size to the size of the window
//	m_pVideoWindow->SetWindowPosition(WinRect.left, WinRect.top, WinRect.right, WinRect.bottom);
//}
//
//void DirectShow::PlayVideo()
//{
//	// play video
//	hr = m_pControl->Run();
//	if(SUCCEEDED(hr))
//		isPlaying = true;
//}
//
//void DirectShow::StopVideo()
//{
//	thisInput->getInput();
//	//closes if video is running
//	if(thisInput->keyPress(DIK_RETURN)) 
//	{
//		m_pControl->Stop();
//		isPlaying = false;
//	}
//
//	m_pEvent->GetEvent(&evCode, &eventParam1, &eventParam2, 0);
//
//	if ( evCode == EC_COMPLETE)
//		isPlaying = false;
//}
//
//void DirectShow::Release(HWND hwnd)
//{
//	m_pControl->Release();
//	m_pVideoWindow->put_Visible(OAFALSE);
//	m_pGraphBuilder->Release();
//	CoUninitialize();
//}
