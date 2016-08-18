#include "EventManager.h"

// class WMQUITmsg;
// class WMCLOSEmsg;
// class WMDESTROYmsg;

// static WMQUITmsg a;
// static WMCLOSEmsg b;
// static WMDESTROYmsg c;

int EventHandler::registerAllmsg()
{
 	static WMQUITmsg a;
	static WMCLOSEmsg b;
	static WMDESTROYmsg c;

	//아래와같이 스텍에서 선언할 경우에는 메모리에서 사라짐으로
	//runMessageLoop 에서 접근할 때 이미 해제된 메모리를 가리키므로 예외가 발생한다. 
	// WMQUITmsg a;
	// WMCLOSEmsg b;
	// WMDESTROYmsg c;

	return 0;
}
bool EventHandler::runMessageLoop(UINT _message)
{
	bool foundMsg = false;
	for(auto& it : MessageHandler::msgs)
	{
		if(it->getMessage() == _message)
		{
			foundMsg = true;
			it->handleMessage();
		}
	}
	return foundMsg;
}



