#include "cheezepizza.h"
#include "papercraftgameconfig.h"
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
}