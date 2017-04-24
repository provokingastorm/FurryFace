#include "cheezepizza.h"
#include "papercraftgameconfig.h"
#include "papercraftplayer.h"
#include "cheezepizzaengine.h"

PapercraftGameConfig::PapercraftGameConfig(PapercraftPlayerShip& InShip)
	: InputConfig()
	, PlayerShip(InShip)
{
}

PapercraftGameConfig::~PapercraftGameConfig()
{
}

void PapercraftGameConfig::HandleInput(float DeltaTime)
{
	HGE& HGEEngine = CheezePizzaEngine::Instance().GetHGE();

	if(HGEEngine.Input_GetKeyState(HGEK_ESCAPE))
	{
		CheezePizzaEngine::Instance().ExitApplication();
	}

	/*if(Handler != NULL)
	{
		PapercraftPlayerHandler& PapercraftHandler = static_cast<PapercraftPlayerHandler&>(*Handler);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
			ScheduledAction Action;
			Action.ActionType = PPA_MoveShipUp;
			PapercraftHandler.ScheduleAction(Action);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
			ScheduledAction Action;
			Action.ActionType = PPA_MoveShipDown;
			PapercraftHandler.ScheduleAction(Action);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
			ScheduledAction Action;
			Action.ActionType = PPA_MoveShipLeft;
			PapercraftHandler.ScheduleAction(Action);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
			ScheduledAction Action;
			Action.ActionType = PPA_MoveShipRight;
			PapercraftHandler.ScheduleAction(Action);
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
			ScheduledAction Action;
			Action.ActionType = PPA_StopMovingShip;
			PapercraftHandler.ScheduleAction(Action);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_SPACE))
		{
			ScheduledAction Action;
			Action.ActionType = PPA_FirePrimaryWeapon;
			PapercraftHandler.ScheduleAction(Action);
		}
	}*/
}

// EOF
