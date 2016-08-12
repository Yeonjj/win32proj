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
	ApplicationManager() = default;
	~ApplicationManager() = default;
private:
	static ApplicationManager *AppManger;

public:
	inline static ApplicationManager* getAppManger() {
		if (AppManger == nullptr) {
			AppManger = new ApplicationManager();
		}
		return AppManger; 
	}
};
ApplicationManager*  ApplicationManager::AppManger;

//status ����
class MasageStatus
{
public:
};


//appmain������ �Ʒ� �Լ����� ȣ���� �� �ֽ��ϴ�. 
inline Internal_vaild LRESULT CALLBACK WindowProcedure(	HWND hwnd, 
														UINT message, 
														WPARAM wParam, 
														LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;

	}
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

	MSG  msg;
	int status;
	//TODO: �̺�Ʈ���� ���� delegate�� ȣ���� ���̴�. delegate�� �������̽��μ� ����ڰ� �����Ѵ�. 
	//���丮 ���ϻ���ؼ� �� �޽������� �ش� delegate�� ȣ�� �� ���̴�. 
	while ((status = ::GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return -1;
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}


