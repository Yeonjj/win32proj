#pragma once
#include <Windows.h>
#include "preheaderinclude.h"

#define Internal_vaild static 
#define local_persist static
#define grobal_variable static

//TODO: �̱��� ���� �̺�Ʈ�������� ��� ���� ��ǲ�� ����. 
class ApplicationManager final
{
private:
	ApplicationManager();
	~ApplicationManager() = default;
	int setRunLoop();
private:
	static ApplicationManager *AppManger;
	bool runState;
public:
	inline static ApplicationManager* getAppManger() {
		if (AppManger == nullptr) {
			AppManger = new ApplicationManager();
		}
		return AppManger; 
	}
};
ApplicationManager*  ApplicationManager::AppManger;

ApplicationManager::ApplicationManager()
{
	//TODO: runloop�� ������ �߰Գ����� ù��° �����ȿ� �ٸ� ���׵��� �߰��� �� �ֵ��� feature �߰��ϱ�.
	setRunLoop();

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
//===================================================================================================
class msgfuncfactory
{
private:
	UNIT message;
public:
	virtual void dothis() = 0;
	virtual void getMessage();
	virtual void setMessage();
};

class WMQUITmsg : public msgfuncfactory
{
 public:
	void dothis();
}
WMQUITmsg::WMQUITmsg()
{
	setMessage(WM_QUIT);
}

void WMQUITmsg::dothis()
{
	::PostQuitMessage(0);
}



class EventHandler
{
public:
	void runEventLoop(UINT _message);
	inline void resisterMessage(msgFuncfacktory msgimpl){ msgs.push_back(msgimpl); }
private:
	vector<msgFuncfactory> msgs;
};

void EventHandler::runEventLoop(UINT _message)
{
	WMQUITmsg WM_QUIT; // TODO:: RAII ����ϱ� 
	resisterMessage(WM_QUIT)
	for(auto it: msgs)
	{
		if(it->getmessage == _message)
		{
			it->dothis
		}
	}
}

//===================================================================================================
class KeyManager
{

};

//status ����
class MasageStatus
{
public:
};

//=====================================================================================================
//appmain������ �Ʒ� �Լ����� ȣ���� �� �ֽ��ϴ�. 
inline Internal_vaild LRESULT CALLBACK WindowProcedure(	HWND hwnd, 
							UINT message, 
							WPARAM wParam, 
							LPARAM lParam)
{
	//TODO: call event manager
	
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

inline Internal_vaild int ApplicationMain
(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow)
{

	//�̱��� ��ü ���� 
	ApplicationManager* AppManager = ApplicationManager::getAppManger();

	wchar_t className[] = L"testingproj";

	WindowClass winClass(WindowProcedure, className, hInst);
	winClass.Register();

	WindowMaker win(className, hInst);

	return msg.wParam;
}


