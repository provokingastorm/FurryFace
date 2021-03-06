#include "cheezepizza.h"
#include "tickable.h"

Tickable::Tickable()
	: TickType(ETT_Tick)
	, ListPrevous(NULL)
	, ListNext(NULL)
{
}

Tickable::~Tickable()
{
	ListPrevous = NULL;
	ListNext = NULL;
}

bool Tickable::WillTick() const
{
	return (ListPrevous != NULL || ListNext != NULL);
}