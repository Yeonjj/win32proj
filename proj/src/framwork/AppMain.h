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
class MessageHandler
{
private:
	UINT message;
	//TODO: RAII pointer�� �ٲٱ� 
	vector <UINT> messageStack;
public:
	inline MessageHandler(UINT _message ){ setMessage(_message); addMsgToStack(_message); } 
	inline virtual void addMsgToStack(UINT _message) { messageStatck.push_back(_message); }
	inline virtual UINT getMessage(){ return message; }
	inline virtual void setMessage(UINT _message){ message = _message; }
	virtual void handleMessage() = 0;
};

class WMQUITmsg : public MessageHandler
{
 public:
	inline WMQUITmsg() : MessageHandler() {}
        virtual ~WMQUITmsg() = default;
	void handleMessage();
};

void WMQUITmsg::handleMessage()
{
	::PostQuitMessage(0);
}

class WMCLOSEmsg : public MessageHandler
{
public:
	inline WMCLSOEmsg() :MessageHandler() {}
	virtual ~WMCLOSEmsg() = default;
	void handleMessage();
};

void WMQUITmsg::handleMessage()
{
	::PostQuitMessage(0);
}

class EventHandler
{
public:
	void runEventLoop(UINT _message);
	inline void useMessage(MessageHandler newHandler){ msgs.push_back(newHandler); }
private:
	vector<MessageHandler *> msgs;
};

void EventHandler::runEventLoop(UINT _message)
{
	for(auto it: msgs)
	{
		if(it->getmessage == _message)
		{
			it->dothis();
		}
	}
}

//somewhere outthere
global_vrialble EventHandler gEventHandler; // TODO:: RAII ����ϱ� pointer�� �ٲٱ�
WMQUITmsg WM_QUIT; // TODO:: RAII ����ϱ� 
gEventHandler->useMessage(WM_QUIT);
	
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
	gEventHandler->runEventLoop(message);
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


