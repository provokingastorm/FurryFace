#include "cheezepizza.h"
#include "papercraftgameconfig.h"
#include "papercraftplayer.h"
#include "cheezepizzaengine.h"

PapercraftGameConfig::PapercraftGameConfig()
	: InputConfig()
{
}

PapercraftGameConfig::PapercraftGameConfig(InputCoordinator& InCoordinator)
	: InputConfig(InCoordinator)
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

	if(Coordinator != NULL)
	{
		PapercraftInputCoordinator& PapercraftCoordinator = static_cast<PapercraftInputCoordinator&>(*Coordinator);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
			PapercraftCoordinator.MoveUp(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
			PapercraftCoordinator.MoveDown(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
			PapercraftCoordinator.MoveLeft(DeltaTime);
		}

		if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
			PapercraftCoordinator.MoveRight(DeltaTime);
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
			PapercraftCoordinator.ResetVelocity();
		}

		if(HGEEngine.Input_GetKeyState(HGEK_SPACE))
		{
			PapercraftCoordinator.FirePrimaryWeapon(DeltaTime);
		}
	}
}

// EOF
