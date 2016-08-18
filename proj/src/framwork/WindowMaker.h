#pragma once
#include "preheaderinclude.h"
//show window
class WindowMaker
{
public:
	WindowMaker() : _windowHandle(0) {}
	inline WindowMaker(char const * className, HINSTANCE hInstance)
	{
		_windowHandle = ::CreateWindowEx(
			NULL,
			className,
			"win32proj",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL);
		//assert(_windowHandle);
	}		
protected:
	HWND _windowHandle;
};
