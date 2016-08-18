#include "EventManager.h"
int EventHandler::registerAllmsg()
{
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



