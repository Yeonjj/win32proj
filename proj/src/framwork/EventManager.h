#pragma once
#include "preheaderinclude.h"
#include "MessageHandler.h"

using std::vector;

class EventHandler
{
public:
	int registerAllmsg();
	bool runMessageLoop(UINT _message);
	//inline vector<MessageHandler*>  getMsgs(){ return msgs; }
	//inline void useMessage(MessageHandler *newHandler){ msgs.push_back(newHandler); }
private:
	//vector<MessageHandler*> msgs;

};

