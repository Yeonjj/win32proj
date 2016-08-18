#include <Windows.h>
#include "AppMain.h"

//extern int ApplicationMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow);

int WINAPI WinMain(	HINSTANCE hInst, 
					HINSTANCE hPrevInst,
					char * cmdParam, 
					int cmdShow)
{
	return ApplicationMain(hInst, hPrevInst, cmdParam, cmdShow);
}
