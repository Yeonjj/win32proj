#include <windows.h>
#include <stdint.h>

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

global_variable BITMAPINFO BitmapInfo;
global_variable	void *BitmapMemory;
global_variable int BitmapWidth;
global_variable int BitmapHeight;
global_variable int BytesPerPixel = 4;

internal void
RenderWindow(int xoffset, int yoffset)
{
	int Width = BitmapWidth;
	int Height = BitmapHeight;
	uint8 *RGB = (uint8 *)BitmapMemory;
	for(int Y = 0;
	    Y < BitmapHeight;
	    ++Y)
	{
		for(int X = 0;
		    X < BitmapWidth;
		    X++)
		{
			*RGB = X+xoffset;
			++RGB;
			
			*RGB = Y+yoffset;
			++RGB;
			
			*RGB = 0;
			++RGB;
				
			*RGB = 0;
			++RGB;
		}
	}
}

//GDI를 적게 사용하고 BITMAP을 만들어 WINDOW에 뿌릴 것이다. 
//device independent bitmap1

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

internal void
ResizeDIBSection(int Width, int Height)
{
	if(BitmapMemory)
        {
		VirtualFree(BitmapMemory, 0, MEM_RELEASE);
	}
	BitmapWidth = Width;
	BitmapHeight = Height;
       	
	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = BitmapWidth;
	BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32; 
	BitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	int BitmapMemorySize = (BitmapWidth*BitmapHeight)*BytesPerPixel;
	BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

	RenderWindow(0,0);
}

internal void
MyUpdateWindow(HDC hdc, RECT *WindowRect, int x, int y, int Width, int Height)
{
	int WindowWidth = WindowRect->right - WindowRect->left;
	int WindowHeight = WindowRect->bottom - WindowRect->top;
	
	StretchDIBits(hdc,
		      /*
		      x, y, Width, Height, // wm paint 메시지로 다시 그릴 사각형 
		      x, y, Width, Height, // src
		      */
		      0,0,BitmapWidth, BitmapHeight,
		      0,0,WindowWidth, WindowHeight,
		      BitmapMemory,
		      &BitmapInfo,
		      DIB_RGB_COLORS,SRCCOPY
		      );
}

int CALLBACK WinMain(
		     HINSTANCE hInstance,
		     HINSTANCE hPrevInstance,
		     LPSTR     lpCmdLine,
		     int       nCmdShow
)
{
	WNDCLASS WindowClass = {}; 	
	WindowClass.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
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
				if(GetMessage(&Message, 0, 0, 0) > 0){
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}else{
					break;
				}
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
		RECT ClientRect; 
		GetClientRect(hWnd, &ClientRect);
		int Width = ClientRect.right - ClientRect.left;
		int Height = ClientRect.bottom - ClientRect.top;
		ResizeDIBSection(Width, Height);
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
	case WM_CHAR:
		if((TCHAR)wParam== 32){
			len = strlen(str);
			str[len] = ' ';
			str[len+1] = 0;
		}
		else{
			len = strlen(str);
			str[len]=(TCHAR)wParam;
			str[len+1]=0;
		}
		InvalidateRect(hWnd,NULL,true);
		return 0;
	case WM_PAINT:
	{
		hdc=BeginPaint(hWnd,&ps);
		int X = ps.rcPaint.left;
		int Y = ps.rcPaint.top;		
		int Height = ps.rcPaint.bottom - ps.rcPaint.top;
		int Width = ps.rcPaint.right - ps.rcPaint.left;

		RECT ClientRect;
		GetClientRect(hWnd, &ClientRect);
		
		MyUpdateWindow(hdc, &ClientRect, X, Y, Width, Height);

		TextOut(hdc,100,100,str,strlen(str));		
		EndPaint(hWnd,&ps);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); //window will handle meg 
	}
	return 0;
}
/*win32 lib provides twe structure wndclass wndclassex. this is infomation about this programm that would be informed to os */

