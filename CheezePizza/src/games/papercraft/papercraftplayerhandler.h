#ifndef PapercraftPlayerHandler_H_
#define PapercraftPlayerHandler_H_

#ifndef ActionHandler_H_
#include "actionhandler.h"
#endif

enum EPapercraftPlayerActions
{
	PPA_MoveShipUp,
	PPA_MoveShipDown,
	PPA_MoveShipLeft,
	PPA_MoveShipRight,
	PPA_StopMovingShip,
	PPA_FirePrimaryWeapon,
};


class PapercraftPlayerHandler : public ActionHandler
{
public:

	PapercraftPlayerHandler();
	~PapercraftPlayerHandler();

	void SetShip(class PapercraftPlayerShip& InShip);

protected:

	// --------------------------------------------------------
	//	Inherited protected functions

	void HandleAction(ScheduledAction& UnhandledAction, float DeltaTime);

private:

	class PapercraftPlayerShip* Ship;
};

#endif

// EOF
