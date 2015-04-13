#ifndef TickLinkedList_H_
#define TickLinkedList_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif


// ----------------------------------------------------------------------------
// Purpose: 
// ----------------------------------------------------------------------------

class TickLinkedList
{
public:
	TickLinkedList(EEngineTickType AssociatedTickType);
	~TickLinkedList() {}

	void Append(Tickable& LinkObj);
	void Remove(Tickable& LinkObj);

	void Tick(float DeltaTime);

private:
	TickLinkedList();

	Tickable* First;
	Tickable* Last;

	EEngineTickType TickType;
};

#endif