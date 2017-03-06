#include "cheezepizza.h"
#include "papercraftplayerhandler.h"
#include "papercraftplayership.h"

PapercraftPlayerHandler::PapercraftPlayerHandler()
{
	SetTickType(ETT_PreTick);
}

PapercraftPlayerHandler::~PapercraftPlayerHandler()
{
	Ship = NULL;
}

void PapercraftPlayerHandler::HandleAction(ScheduledAction& UnhandledAction, float DeltaTime)
{
	switch(UnhandledAction.ActionType)
	{
	case PPA_MoveShipUp:
		Ship->MoveVertical(1.0f, DeltaTime);
		break;

	case PPA_MoveShipDown:
		Ship->MoveVertical(-1.0f, DeltaTime);
		break;

	case PPA_MoveShipLeft:
		Ship->MoveHorizontal(-1.0f, DeltaTime);
		break;

	case PPA_MoveShipRight:
		Ship->MoveHorizontal(1.0f, DeltaTime);
		break;
		
	case PPA_StopMovingShip:
		Ship->ResetVelocity();
		break;

	case PPA_FirePrimaryWeapon:
		//Ship->FirePrimaryWeapon();
		break;

	default:
		break;
	}
}

void PapercraftPlayerHandler::SetShip(class PapercraftPlayerShip& InShip)
{
	Ship = &InShip;
}

// EOF
