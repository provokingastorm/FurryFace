#include "cheezepizza.h"
#include "actionhandler.h"

// ----------------------------------------------------------------------------
// ActionHandler - Definition
// ----------------------------------------------------------------------------

ActionHandler::ActionHandler()
{
}

ActionHandler::~ActionHandler()
{
}

void ActionHandler::ScheduleAction(ScheduledAction& Action)
{
	ActionStack.push_back(Action);
}

void ActionHandler::HandleAction(ScheduledAction& UnhandledAction, float DeltaTime)
{
	// Intentionally left blank
}

void ActionHandler::Tick(float DeltaTime)
{
	const int NumActions = ActionStack.size();
	for(int i = 0; i < NumActions; ++i)
	{
		HandleAction(ActionStack[i], DeltaTime);
	}

	ActionStack.clear();
}

// EOF
