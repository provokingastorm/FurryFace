#include "cheezepizza.h"
#include "sharedinputconfigs.h"
#include "localplayer.h"
#include "cheezepizzaengine.h"

DefaultEngineConfig::DefaultEngineConfig()
	:	InputConfig()
{
}

DefaultEngineConfig::DefaultEngineConfig(LocalPlayer& AssignedPlayer)
	:	InputConfig(AssignedPlayer)
{
}

DefaultEngineConfig::~DefaultEngineConfig()
{
}

void DefaultEngineConfig::GetKeyUpEvents(std::vector<int>& KeyUpEvents)
{
	KeyUpEvents.push_back(HGEK_ESCAPE);
}

void DefaultEngineConfig::OnKeyUp(int KeyID)
{
	switch(KeyID)
	{
	case HGEK_ESCAPE:
		CheezePizzaEngine::Instance().ExitApplication();
		break;

	default:
		break;
	}
}