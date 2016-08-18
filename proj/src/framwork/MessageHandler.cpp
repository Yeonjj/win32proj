#include "MessageHandler.h"

//NOTE: okay to do that?
vector<MessageHandler*> MessageHandler::msgs;

void WMQUITmsg::handleMessage()
{
	::PostQuitMessage(0);
}
void WMCLOSEmsg::handleMessage()
{
	::PostQuitMessage(0);
}
void WMDESTROYmsg::handleMessage()
{
	::PostQuitMessage(0);
}

