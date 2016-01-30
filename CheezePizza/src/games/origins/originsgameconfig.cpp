#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "cheezepizzaengine.h"
#include "originsplayer.h"

OriginsGameConfig::OriginsGameConfig()
	: InputConfig()
{
}

OriginsGameConfig::OriginsGameConfig(LocalPlayer& AssignedPlayer)
	: InputConfig(AssignedPlayer)
{
}

OriginsGameConfig::~OriginsGameConfig()
{
}

void OriginsGameConfig::HandleInput(float DeltaTime)
{
	HGE& HGEEngine = CheezePizzaEngine::Instance().GetHGE();

	if(HGEEngine.Input_GetKeyState(HGEK_ESCAPE))
	{
		CheezePizzaEngine::Instance().ExitApplication();
	}

	if(Player != NULL)
	{
		OriginsPlayer& OriginsLocalPlayer = static_cast<OriginsPlayer&>(*Player);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
			OriginsLocalPlayer.MoveUp(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
			OriginsLocalPlayer.MoveDown(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
			OriginsLocalPlayer.MoveLeft(DeltaTime);
		}
		else if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
			OriginsLocalPlayer.MoveRight(DeltaTime);
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
			OriginsLocalPlayer.ResetVelocity();
		}
	}
}

// EOF
