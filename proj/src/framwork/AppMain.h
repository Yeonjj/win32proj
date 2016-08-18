#pragma once
#include <Windows.h>
#include "preheaderinclude.h"
#include "MessageHandler.h"
#include "EventManager.h"
#include <iostream>
#include <vector>

using namespace std;


//appmain에서만 아래 함수들을 호출할 수 있습니다. 
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam);
int ApplicationMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow, const char* classNmae);

//TODO: 싱글톤 구현 이벤트루프관리 모든 유저 인풋을 관리. 
class ApplicationManager final
{
private:
	ApplicationManager();
	~ApplicationManager() = default;
	
	static ApplicationManager *AppManger;
	bool runState;
public:
	int setMessages();
	int setRunLoop();
	static ApplicationManager* getAppManger();
};

//TODO: keymanager
class KeyManager
{

};

