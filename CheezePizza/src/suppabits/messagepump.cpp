#include "cheezepizza.h"
#include "messagepump.h"

MessagePump::MessagePump()
{
}

MessagePump::~MessagePump()
{
}

void MessagePump::RegisterForMessages(class EngineSubsystem& Subsystem, int MessageType)
{
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, float Timeout, float Delay)
{
	Message& Msg = *(new Message(ID, HandlingType));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, int MessageData, float Timeout, float Delay)
{
	MessageInt& Msg = *(new MessageInt(ID, HandlingType, MessageData));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, float MessageData, float Timeout, float Delay)
{
	MessageFloat& Msg = *(new MessageFloat(ID, HandlingType, MessageData));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, bool MessageData, float Timeout, float Delay)
{
	MessageBool& Msg = *(new MessageBool(ID, HandlingType, MessageData));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, double MessageData, float Timeout, float Delay)
{
	MessageDouble& Msg = *(new MessageDouble(ID, HandlingType, MessageData));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageToQueue(int ID, EMessageHandlingType HandlingType, void* MessageData, float Timeout, float Delay)
{
	MessagePointer& Msg = *(new MessagePointer(ID, HandlingType, MessageData));
	Msg.Timeout = Timeout;
	Msg.DeliveryDelay = Delay;
	AddMessageInternal(Msg);
}

void MessagePump::AddMessageInternal(class Message& Msg)
{
}

void MessagePump::ProcessMessages(float DeltaTime)
{
}
