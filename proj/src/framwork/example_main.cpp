#include <Windows.h>
#include "AppMain.h"

int WINAPI WinMain(	HINSTANCE hInst, 
					HINSTANCE hPrevInst,
					char * cmdParam, 
					int cmdShow)
{
	return ApplicationMain(hInst, hPrevInst, cmdParam, cmdShow);
}
