#pragma once
#include <Windows.h>
#include "preheaderinclude.h"

#define Internal_vaild static 
#define local_persist static
#define grobal_variable static

//TODO: 싱글톤 구현 이벤트루프관리 모든 유저 인풋을 관리. 
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
	//TODO: runloop의 루프를 잘게나눠서 첫번째 루프안에 다른 사항들을 추가할 수 있도록 feature 추가하기.
	setRunLoop();

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

//===================================================================================================
class MessageHandler
{
private:
	UINT message;
	//TODO: RAII pointer로 바꾸기 
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
global_vrialble EventHandler gEventHandler; // TODO:: RAII 사용하기 pointer로 바꾸기
WMQUITmsg WM_QUIT; // TODO:: RAII 사용하기 
gEventHandler->useMessage(WM_QUIT);
	
//===================================================================================================
class KeyManager
{

};

//status 구현
class MasageStatus
{
public:
};

//=====================================================================================================
//appmain에서만 아래 함수들을 호출할 수 있습니다. 
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

	//싱글톤 객체 생성 
	ApplicationManager* AppManager = ApplicationManager::getAppManger();

	wchar_t className[] = L"testingproj";

	WindowClass winClass(WindowProcedure, className, hInst);
	winClass.Register();

	WindowMaker win(className, hInst);

	return msg.wParam;
}


