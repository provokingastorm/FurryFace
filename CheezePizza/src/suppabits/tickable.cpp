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
}

bool Tickable::WillTick() const
{
	return (ListPrevous != NULL && ListNext != NULL);
}

void Tickable::StopTicking()
{
}