#pragma once
//#include "EventManager.h"
#include <iostream>
#include <vector>
#include "preheaderinclude.h"

using std::vector;
class MessageHandler
{
private:
	UINT message;
	//TODO: RAII pointer�� �ٲٱ�
public:
	static vector<MessageHandler*> msgs;
public:
	inline MessageHandler(UINT _message){ setMessage(_message); registerMsg(this); }
	virtual void handleMessage() = 0;

	inline void registerMsg(MessageHandler *handlerObj) { msgs.push_back(handlerObj); }
	inline UINT getMessage(){ return message; }
	inline void setMessage(UINT _message){ message = _message; }
};

class WMQUITmsg : public MessageHandler
{
public:
	inline WMQUITmsg() : MessageHandler(WM_QUIT) {}
	void handleMessage();
};

class WMCLOSEmsg : public MessageHandler
{
public:
	inline WMCLOSEmsg() : MessageHandler(WM_CLOSE) {}
	void handleMessage();
};

class WMDESTROYmsg : public MessageHandler
{
public:
	inline WMDESTROYmsg() : MessageHandler(WM_DESTROY) {}
	void handleMessage();
};
