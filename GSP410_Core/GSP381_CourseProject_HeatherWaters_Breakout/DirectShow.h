//#pragma once
//
//#include <DShow.h>
//#include "2dSurface.h"
//
//class InputManager;
//
//#pragma comment(lib, "strmiids.lib")
//
//class DirectShow
//{
//	HRESULT			hr;
//
//	IGraphBuilder*	m_pGraphBuilder;
//	IMediaControl*	m_pControl;
//	IMediaEvent*	m_pEvent;
//	IVideoWindow*	m_pVideoWindow;
//	long			evCode;
//
//	LONG_PTR		eventParam1;
//	LONG_PTR		eventParam2;
//
//	InputManager*	thisInput;
//
//public:
//	bool			isPlaying;
//
//	DirectShow(void);
//	~DirectShow(void);
//
//	void Initialize(HWND hwnd, InputManager* input, bool fullscreen);
//	void PlayVideo();
//	void StopVideo();
//	void Release(HWND hwnd);
//};
//
