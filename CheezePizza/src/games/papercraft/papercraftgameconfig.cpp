#include "cheezepizza.h"
#include "papercraftgameconfig.h"
#include "papercraftplayer.h"
#include "papercraftinputhandler.h"
#include "cheezepizzaengine.h"

PapercraftGameConfig::PapercraftGameConfig()
	: InputConfig()
{
}

PapercraftGameConfig::PapercraftGameConfig(InputHandler& InHandler)
	: InputConfig(InHandler)
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

	if(Handler != NULL)
	{
		PapercraftInputHandler& PapercraftHandler = static_cast<PapercraftInputHandler&>(*Handler);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
			PapercraftHandler.MoveUp(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
			PapercraftHandler.MoveDown(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
			PapercraftHandler.MoveLeft(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
			PapercraftHandler.MoveRight(DeltaTime);
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
			PapercraftHandler.ResetVelocity();
		}

		if(HGEEngine.Input_GetKeyState(HGEK_SPACE))
		{
			PapercraftHandler.FirePrimaryWeapon(DeltaTime);
		}
	}
}

// EOF
