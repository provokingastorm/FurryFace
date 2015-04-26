#ifndef MessageTypes_H_
#define MessageTypes_H_

#ifndef DebugUtilities_H_
#include "debugutilities.h"
#endif

enum EMessageHandlingType
{
	MHT_DeliverOnce,
	MHT_ReceivedOrTimedOut,
	MHT_TimeOutOnly,
};

class Message
{
public:
	Message(int ID, EMessageHandlingType HandlingType)
		: MessageID(ID)
		, HandlingRule(HandlingType)
		, DeliveryDelay(0.0f)
		, SentTimestamp(0.0)
		, RecievedTimestamp(0.0)
	{
		CPAssert(ID > 0, "Message: Invalid MessageID provided");
	}

	virtual ~Message() {}

	// The unique type of message
	const int MessageID;

	// Instructions on how to handle this message
	const EMessageHandlingType HandlingRule;

	// The amount of time to wait before delivering
	float DeliveryDelay;

	// The amount of elapsed time until timing out
	float Timeout;

	// The timestamp of the world when the message is added to the message pump
	double SentTimestamp;

	// The timestamp of the world when the message was processed
	double RecievedTimestamp;

private:
	Message();
};

class MessageInt : public Message
{
public:
	MessageInt(int ID, EMessageHandlingType HandlingType, int Data)
		: Message(ID, HandlingType)
		, IntData(Data)
	{
	}

	const int IntData;
};

class MessageFloat : public Message
{
public:
	MessageFloat(int ID, EMessageHandlingType HandlingType, float Data)
		: Message(ID, HandlingType)
		, FloatData(Data)
	{
	}

	const float FloatData;
};

class MessageBool : public Message
{
public:
	MessageBool(int ID, EMessageHandlingType HandlingType, bool Data)
		: Message(ID, HandlingType)
		, bData(Data)
	{
	}

	const bool bData;
};

class MessageDouble : public Message
{
public:
	MessageDouble(int ID, EMessageHandlingType HandlingType, double Data)
		: Message(ID, HandlingType)
		, DoubleData(Data)
	{
	}

	const double DoubleData;
};

class MessagePointer : public Message
{
public:
	MessagePointer(int ID, EMessageHandlingType HandlingType, void* Data)
		: Message(ID, HandlingType)
		, PointerData(Data)
	{
	}

	const void* PointerData;
};


#endif