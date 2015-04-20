#ifndef MessagePump_H_
#define MessagePump_H_

#ifndef MessageTypes_H_
#include "messagetypes.h"
#endif

class MessagePump
{
public:
	MessagePump();
	~MessagePump();

	void RegisterForMessages(class EngineSubsystem& Subsystem, int MessageType);

	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, float Timeout=0.0f, float Delay=0.0f);
	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, int MessageData, float Timeout=0.0f, float Delay=0.0f);
	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, float MessageData, float Timeout=0.0f, float Delay=0.0f);
	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, bool MessageData, float Timeout=0.0f, float Delay=0.0f);
	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, double MessageData, float Timeout=0.0f, float Delay=0.0f);
	void AddMessageToQueue(int ID, EMessageHandlingType HandlingType, void* MessageData, float Timeout=0.0f, float Delay=0.0f);

	void ProcessMessages(float DeltaTime);

private:
	void AddMessageInternal(class Message& Msg);
};

#endif