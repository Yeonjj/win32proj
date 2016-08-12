#pragma once
#include "preheaderinclude.h"
//create windowclass and register
class WindowClass
{
public:
	inline WindowClass(WNDPROC winProc,
		const wchar_t* className,
		HINSTANCE hInstance)
	{
		_winclass = {0};
		_winclass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		_winclass.hInstance = hInstance;
		_winclass.lpfnWndProc = winProc;
		_winclass.lpszClassName = className;
		_winclass.hCursor = LoadCursor(NULL, IDC_CROSS);
 
	}
	inline bool Register()
	{
		if(::RegisterClassW(&_winclass)) return true;
		else return false;
	}
private:
	WNDCLASS _winclass;
};
