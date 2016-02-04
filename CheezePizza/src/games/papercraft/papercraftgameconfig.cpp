#include "cheezepizza.h"
#include "papercraftgameconfig.h"
#include "papercraftplayer.h"
#include "cheezepizzaengine.h"

PapercraftGameConfig::PapercraftGameConfig()
	: InputConfig()
{
}

PapercraftGameConfig::PapercraftGameConfig(LocalPlayer& AssignedPlayer)
	: InputConfig(AssignedPlayer)
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

	if(Player != NULL)
	{
		PapercraftPlayer& PapercraftLocalPlayer = static_cast<PapercraftPlayer&>(*Player);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
			PapercraftLocalPlayer.MoveUp(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
			PapercraftLocalPlayer.MoveDown(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
			PapercraftLocalPlayer.MoveLeft(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
			PapercraftLocalPlayer.MoveRight(DeltaTime);
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
			PapercraftLocalPlayer.ResetVelocity();
		}
	}
}