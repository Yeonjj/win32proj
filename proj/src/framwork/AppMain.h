#pragma once
#include <Windows.h>
#include "preheaderinclude.h"
#include "MessageHandler.h"
#include "EventManager.h"
#include <iostream>
#include <vector>

using namespace std;


//appmain������ �Ʒ� �Լ����� ȣ���� �� �ֽ��ϴ�. 
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam);
int ApplicationMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow, const char* classNmae);

//TODO: �̱��� ���� �̺�Ʈ�������� ��� ���� ��ǲ�� ����. 
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

