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

	//�Ʒ��Ͱ��� ���ؿ��� ������ ��쿡�� �޸𸮿��� ���������
	//runMessageLoop ���� ������ �� �̹� ������ �޸𸮸� ����Ű�Ƿ� ���ܰ� �߻��Ѵ�. 
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



