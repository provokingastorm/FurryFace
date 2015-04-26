#include "cheezepizza.h"
#include "ticklinkedlist.h"
#include "tickable.h"

TickLinkedList::TickLinkedList()
	: First(NULL)
	, Last(NULL)
	, TickType(ETT_Tick)
{
}

TickLinkedList::~TickLinkedList()
{
	First = NULL;
	Last = NULL;
}

void TickLinkedList::SetTickType(EEngineTickType AssociatedTickType)
{
	TickType = AssociatedTickType;
}

void TickLinkedList::Append(Tickable& LinkObj)
{
	// Immediately exit the function if the Tickable object is already in a tick list
	if(LinkObj.ListPrevous != NULL || LinkObj.ListNext != NULL)
	{
		return;
	}

	// Add as the first item in the list
	if(First == NULL)
	{
		CPAssert(Last == NULL, "TickLinkedList: the last node should never be valid when the first node is invalid");

		LinkObj.ListPrevous = NULL;
		LinkObj.ListNext = NULL;
		First = &LinkObj;
	}
	// Only one node in the linked list
	else if(Last == NULL)
	{
		CPAssert(First->ListNext == NULL, "TickLinkedList: the first node's Next pointer should never be valid when the last node is invalid");
		CPAssert(First->ListPrevous == NULL, "TickLinkedList: the first node should never have a valid Prev pointer");

		First->ListNext = &LinkObj;
		LinkObj.ListPrevous = First;
		Last = &LinkObj;
	}
	// Insert the node somewhere in the middle of the list
	else
	{
		CPAssert(First->ListPrevous == NULL, "TickLinkedList: the first node should never have a valid Prev pointer");
		CPAssert(First->ListNext != NULL, "TickLinkedList: the first node's Next pointer should always be valid when we have a valid Last node");
		CPAssert(Last->ListPrevous != NULL, "TickLinkedList: the Last node's Prev pointer should always be valid");
		CPAssert(Last->ListNext == NULL, "TickLinkedList: the first node's Next pointer should never be valid when the last node is invalid");

		Last->ListNext = &LinkObj;
		LinkObj.ListPrevous = Last;
		Last = &LinkObj;
	}

	// Notify that object that they were added to the tick list to do any initialization
	LinkObj.OnTickStarted();
}

void TickLinkedList::Remove(Tickable& LinkObj)
{
	if(LinkObj.ListNext == NULL && LinkObj.ListPrevous == NULL)
	{
		CPForceAssert("TickLinkedList: Attempting to remove a Tickable that isn't in any tick list");
		return;
	}

	const bool bIsSameTickType = (LinkObj.GetTickType() == TickType);
	if(!bIsSameTickType)
	{
		CPForceAssert("TickLinkedList: Trying to remove a Tickable object that does not match the tick type");
		return;
	}

	// Notify that object that they will be removed from the tick list so they can cleanup
	LinkObj.OnTickStopped();

	// Removing the first object in the list
	if(First == &LinkObj)
	{
		CPAssert(First->ListPrevous == NULL, "TickLinkedList: ");

		if(LinkObj.ListNext != NULL)
		{
			First->ListNext->ListPrevous = NULL;
			First = LinkObj.ListNext;

			// There were only two objects in the list. Clear Last because First should never equal Last.
			if(First == Last)
			{
				Last = NULL;
			}
		}
		else
		{
			First = NULL;
		}
	}
	// Removing the last object in the list
	else if(Last == &LinkObj)
	{
		CPAssert(Last->ListPrevous != NULL, "TickLinkedList: The last object in the list should always have a valid previous pointer");

		Last->ListPrevous->ListNext = NULL;
		Last = Last->ListPrevous;
	}
	// Removing an object from the middle of the list
	else
	{
		CPAssert(LinkObj.ListPrevous != NULL, "TickLinkedList: Trying to removing an object from the middle with an invalid Prev pointer");
		CPAssert(LinkObj.ListNext != NULL, "TickLinkedList: Trying to removing an object from the middle with an invalid Next pointer");

		LinkObj.ListPrevous->ListNext = LinkObj.ListNext;
		LinkObj.ListNext->ListPrevous = LinkObj.ListPrevous;
	}

	LinkObj.ListPrevous = NULL;
	LinkObj.ListNext = NULL;
}

void TickLinkedList::Tick(float DeltaTime)
{
	if(First != NULL)
	{
		if(Last != NULL)
		{
			Tickable* Current = First;
			while(Current != NULL && Current != Last)
			{
				Current->Tick(DeltaTime);
				Current = Current->ListNext;
			}
		}
		else
		{
			First->Tick(DeltaTime);
		}
	}
}