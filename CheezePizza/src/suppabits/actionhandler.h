#ifndef ActionHandler_H_
#define ActionHandler_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

struct ScheduledAction
{
	int ActionType;
	bool bIsPersistent;
};

// ----------------------------------------------------------------------------
// ActionHandler - Declaration
// ----------------------------------------------------------------------------

class ActionHandler : public Tickable
{
public:

	ActionHandler();
	virtual ~ActionHandler();

	void ScheduleAction(ScheduledAction& Action);

protected:

	virtual void HandleAction(ScheduledAction& UnhandledAction, float DeltaTime);

private:

	void Tick(float DeltaTime);

	std::vector<ScheduledAction> ActionStack;
};


#endif

// EOF
