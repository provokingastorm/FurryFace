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
	TickLinkedList();
	~TickLinkedList();

	void SetTickType(EEngineTickType AssociatedTickType);

	void Append(Tickable& LinkObj);
	void Remove(Tickable& LinkObj);

	void Tick(float DeltaTime);

private:

	Tickable* First;
	Tickable* Last;

	EEngineTickType TickType;
};

#endif