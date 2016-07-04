#include "cheezepizza.h"
#include "papercraftgameconfig.h"
#include "papercraftplayer.h"
#include "papercraftplayerhandler.h"
#include "cheezepizzaengine.h"

PapercraftGameConfig::PapercraftGameConfig()
	: InputConfig()
{
}

PapercraftGameConfig::PapercraftGameConfig(ActionHandler& InHandler)
	: InputConfig(InHandler)
{
}

PapercraftGameConfig::~PapercraftGameConfig()
{
	Handler = NULL;
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
		PapercraftPlayerHandler& PapercraftHandler = static_cast<PapercraftPlayerHandler&>(*Handler);

		if(HGEEngine.Input_GetKeyState(HGEK_W))
		{
		}

		if(HGEEngine.Input_GetKeyState(HGEK_S))
		{
		}

		if(HGEEngine.Input_GetKeyState(HGEK_A))
		{
		}

		if(HGEEngine.Input_GetKeyState(HGEK_D))
		{
		}

		if(		HGEEngine.Input_KeyUp(HGEK_W)
			||	HGEEngine.Input_KeyUp(HGEK_S)
			||	HGEEngine.Input_KeyUp(HGEK_A)
			||	HGEEngine.Input_KeyUp(HGEK_D)
			)
		{
		}

		if(HGEEngine.Input_GetKeyState(HGEK_SPACE))
		{
		}
	}
}

// EOF
