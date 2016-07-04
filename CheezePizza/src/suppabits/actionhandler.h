#ifndef ActionHandler_H_
#define ActionHandler_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif

// ----------------------------------------------------------------------------
// ActionHandler - Declaration
// ----------------------------------------------------------------------------

class ActionHandler : public Tickable
{
public:

	ActionHandler();

	void ScheduleAction(int ActionType);

private:

	void Tick(float DeltaTime);
};


#endif

// EOF
