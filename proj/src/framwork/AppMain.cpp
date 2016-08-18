#include "AppMain.h"

static EventHandler gEventHandler;

ApplicationManager*  ApplicationManager::AppManger;
ApplicationManager::ApplicationManager()
{
	//TODO: runloop�� ������ �߰Գ����� ù��° �����ȿ� �ٸ� ���׵��� �߰��� �� �ֵ��� feature �߰��ϱ�.
	//setRunLoop();
}

int ApplicationManager::setRunLoop()
{
	MSG  msg;
	runState = true;
	//TODO: �̺�Ʈ���� ���� delegate�� ȣ���� ���̴�. delegate�� �������̽��μ� ����ڰ� �����Ѵ�. 
	//���丮 ���ϻ���ؼ� �� �޽������� �ش� delegate�� ȣ�� �� ���̴�. 
	while(runState)
	{
		//TODO: �� �ȿ��� �ٸ� �۾��� �� �� �ֵ��� ������. 
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
		return ::DefWindowProc(hwnd, message, wParam, lParam);
	return 0;
}

int ApplicationMain (HINSTANCE hInst,
		     HINSTANCE hPrevInst,
		     char *cmdParam,
		     int cmdShow,
		     const char *className)
{
	//�̱��� ��ü ����
	ApplicationManager* AppManager = ApplicationManager::getAppManger();
	
	//char className[] = "testingproj";
	//TODO: 1. initialize windowclass and register
	WindowClass winClass(WindowProcedure, className, hInst);
	if(winClass.Register())
	{
	//TODO: 2. initialize window instance and create window
		WindowMaker win(className, hInst);
		AppManager->setMessages();
	//TODO: 3. set message loop
		AppManager->setRunLoop();
	}		
	return 0;
}



