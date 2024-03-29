#include <windows.h>
#include <stdint.h>
#include <dsound.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

#define local_persist static
#define global_variable static 
#define internal static 

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

using namespace std;

global_variable bool Running; // = 0;
global_variable	int xoffset;  // = 0;
global_variable	int yoffset;  // = 0;

//TODO:pitch 없에기 
struct win32_screen_buffer
{
	BITMAPINFO BitmapInfo;
	void *BitmapMemory;
	int BitmapWidth;
	int BitmapHeight;
	int BytesPerPixel;
	int Pitch;
};

global_variable win32_screen_buffer gBitmapBuffer;

internal void
initDSound(void)
{
	//TODO: load the lib
	HMODULE soundLib = LoadLibraryA("dsound.dll");
	//TODO: get a directsound object!
	//TODO: creaet a primary buffer 
	//TODO: create a secondary buffer
	if(soundLib)
	{
		
	}
}

internal void
RenderWindow(win32_screen_buffer &buffer, int xoffset, int yoffset)
{
	uint8 *Row = (uint8 *)buffer.BitmapMemory;
	for(int Y = 0; Y < buffer.BitmapHeight; ++Y)
	{
		uint32 *Pixel = (uint32 *)Row;
		for(int X = 0; X < buffer.BitmapWidth; X++)
		{
			uint8 blue = (X+xoffset);
			uint8 green = (Y+yoffset);
			*Pixel++ = ((green << 8) | blue);
		}
		Row += buffer.Pitch;
	}
}

//GDI를 적게 사용하고 BITMAP을 만들어 WINDOW에 뿌릴 것이다. 
//device independent bitmap1

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//bitmap sturcture
/*
  file header BITMAPFILEHEADER
  image header BITMAPINFOHEADER
  color table
  pixel date
*/
internal void
ResizeDIBSection(win32_screen_buffer &buffer, int Width, int Height)
{
	//BITMAPINFOHEADER
	if(buffer.BitmapMemory)
        {
		VirtualFree(buffer.BitmapMemory, 0, MEM_RELEASE);
	}
	buffer.BitmapWidth = Width;
	buffer.BitmapHeight = Height;
       	buffer.BytesPerPixel = 4;
	buffer.Pitch = buffer.BitmapWidth*buffer.BytesPerPixel;

	buffer.BitmapInfo.bmiHeader.biSize = sizeof(buffer.BitmapInfo.bmiHeader);
	buffer.BitmapInfo.bmiHeader.biWidth = buffer.BitmapWidth;
	buffer.BitmapInfo.bmiHeader.biHeight = -buffer.BitmapHeight;
	buffer.BitmapInfo.bmiHeader.biPlanes = 1;
	buffer.BitmapInfo.bmiHeader.biBitCount = 32; 
	buffer.BitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	int BitmapMemorySize = (buffer.BitmapWidth*buffer.BitmapHeight)*buffer.BytesPerPixel;
	buffer.BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

	RenderWindow(buffer,0,0);
}

internal void
MyUpdateWindow(HDC hdc, win32_screen_buffer &buffer, int x, int y, int Width, int Height)
{
	StretchDIBits(hdc,
		      /*
		      x, y, Width, Height, // wm paint 메시지로 다시 그릴 사각형 
		      x, y, Width, Height, // src
		      */
		      0, 0, Width, Height,
		      0, 0, buffer.BitmapWidth, buffer.BitmapHeight,
		      buffer.BitmapMemory,
		      &buffer.BitmapInfo,
		      DIB_RGB_COLORS,SRCCOPY
		      );
}
/*
DWORD WINAPI
ThreadProc(LPVOID arg)
{
	char *str = (char*)arg;
	while(true)
	{
		OutputDebugString(str);
		Sleep(1000);
		while(Running){
			MSG Message;
			while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
				if(Message.message == WM_QUIT){
					Running = false;
				}
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
			if( xoffset<=255 || yoffset<=255 )
				{
					xoffset++;
					yoffset++;
				}
			else
				{
					xoffset = 0;
					yoffset = 0;
				}
			RenderWindow(xoffset, yoffset);
			InvalidateRect(WindowHandle, 0, false);
		}
	}
	return 0;
}
*/

int CALLBACK WinMain(
		     HINSTANCE hInstance,
		     HINSTANCE hPrevInstance,
		     LPSTR     lpCmdLine,
		     int       nCmdShow
)
{
	ResizeDIBSection(gBitmapBuffer, 1184, 810);
	// char *str = "yay it works!!\n";
	// DWORD threadID;
	// HANDLE ThreadHandle = CreateThread(0, 0, ThreadProc, str, 0, &threadID);
	// CloseHandle(ThreadHandle); //return thread to os
	WNDCLASS WindowClass = {};
	//TODO:style 과 dc 화면을 다시 그리는 것과의 관계
	WindowClass.style         = CS_HREDRAW|CS_VREDRAW;
        WindowClass.hInstance     = hInstance; 
	//만약 두개의 메모장이 실행되고있다면 , 두개의 인스턴스 핸들값은 다르다. 이를 통해 os에서 구분한다. 
	/*보통 프로그램이 메모리 상에 올라가 있는 시작주소값을 가지고 있다.*/
        WindowClass.lpfnWndProc   = WndProc; 
        WindowClass.lpszClassName = "projClass"; 
	//WindowClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	WindowClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	
	if(RegisterClass(&WindowClass)){
		HWND WindowHandle =
			CreateWindowEx(
				       NULL,
				       WindowClass.lpszClassName,
				       "testproj",
				       WS_OVERLAPPEDWINDOW|WS_VISIBLE,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       NULL,
				       NULL,
				       hInstance,
				       NULL);
		if(WindowHandle){
		
			Running = true; 
			while(Running){
				MSG Message;
				//윈도우가 열린뒤에 소리 로드;
				initDSound(); 
				
				//수행후에는 메시지가 제거되고 0을 반환함으로 메시지가 있을 경우에만 수행된다.
				//만약 화면을 리사이징하고자 가장자리를 클릭했다고하자 다음 루프가 돌면서
				//빠저나오지 않고 계속 winporc 콜백 함수를 호출하게 될 것이다.
				while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){ 
					if(Message.message == WM_QUIT){
						Running = false;
					}
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				
				
				xoffset++;

				HDC hdc = GetDC(WindowHandle);
				RECT rect;

				GetClientRect(WindowHandle, &rect);
				int wndWidth = rect.right - rect.left;
				int wndHeight = rect.bottom - rect.top;
				//ResizeDIBSection(gBitmapBuffer, wndWidth, wndHeight);  
				RenderWindow(gBitmapBuffer, xoffset, yoffset);
				MyUpdateWindow(hdc, gBitmapBuffer, 0, 0,  wndWidth, wndHeight);
				ReleaseDC(WindowHandle, hdc);
			}
		}else{
			//TODO: 
		}
	}else{
		//TODO: 
	}
	return 0;
}

//Windows controls will interact with the com and user.
LRESULT CALLBACK WndProc(HWND hWnd,
			 UINT uMsg,
			 WPARAM wParam,
			 LPARAM lParam)
{
	
	HDC hdc;
	PAINTSTRUCT ps;
	
	local_persist char str[256];
	int len;

	switch (uMsg)
	{
	case WM_SIZE:
	{
		break;
	}
	case WM_DESTROY:
		Running = false;
		break;
	case WM_CLOSE:
		Running = false; 
		break;
	case WM_ACTIVATEAPP:
		break;
	case WM_KEYDOWN:
	{
		if(wParam == VK_RIGHT)
			xoffset+=10;
		else if(wParam == VK_LEFT)
			xoffset-=10;
		else if(wParam == VK_UP)
			yoffset+=10;
		else if(wParam == VK_DOWN)
			yoffset-=10;
		break;
	}
	case WM_PAINT:
	{
		hdc=BeginPaint(hWnd,&ps);
		int X = ps.rcPaint.left;
		int Y = ps.rcPaint.top;		
		int Height = ps.rcPaint.bottom - ps.rcPaint.top;
		int Width = ps.rcPaint.right - ps.rcPaint.left;
		RECT ClientRect;
		GetClientRect(hWnd, &ClientRect);		
		MyUpdateWindow(hdc, gBitmapBuffer, X, Y, Width, Height);
		EndPaint(hWnd,&ps);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); //window will handle meg 
	}
	return 0;
} 
/*win32 lib provides twe structure wndclass wndclassex. this is infomation about this programm that would be informed to os */

