#include "AppMain.h"

static EventHandler gEventHandler;
ApplicationManager*  ApplicationManager::AppManger;

ApplicationManager::ApplicationManager()
{
	//TODO: runloop의 루프를 잘게나눠서 첫번째 루프안에 다른 사항들을 추가할 수 있도록 feature 추가하기.
	//setRunLoop();
}

int ApplicationManager::setRunLoop()
{
	MSG  msg;
	runState = true;
	//TODO: 이벤트루프 구성 delegate를 호출할 것이다. delegate는 인터페이스로서 사용자가 구현한다. 
	//팩토리 페턴사용해서 각 메시지마다 해당 delegate를 호출 할 것이다. 
	while(runState)
	{
		//TODO: 이 안에서 다른 작업을 할 수 있도록 나누기. 
		while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				runState = false;
			::DispatchMessage(&msg);
		}
	}
	
	return 0;
}

int ApplicationManager::setMessages()
{
	gEventHandler.registerAllmsg();
	return 0;
}

ApplicationManager* ApplicationManager::getAppManger()
{
	if (AppManger == nullptr) {
		AppManger = new ApplicationManager();
	}
	return AppManger;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, 
					UINT message, 
					WPARAM wParam, 
					LPARAM lParam)
{
	//TODO: call event manager
	//TODO: message setting
	if(!gEventHandler.runMessageLoop(message))
		::DefWindowProc(hwnd, message, wParam, lParam);
	return 0;
}

int ApplicationMain (HINSTANCE hInst,
			    HINSTANCE hPrevInst,
			    char * cmdParam,
			    int cmdShow)
{
	//싱글톤 객체 생성 
	ApplicationManager* AppManager = ApplicationManager::getAppManger();

	char className[] = "testingproj";

	WindowClass winClass(WindowProcedure, className, hInst);
	if(winClass.Register())
	{
		WindowMaker win(className, hInst);
		AppManager->setMessages();
		AppManager->setRunLoop();
	}		
	return 0;
}



