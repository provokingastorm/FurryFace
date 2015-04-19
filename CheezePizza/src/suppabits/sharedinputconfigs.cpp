#include "cheezepizza.h"
#include "sharedinputconfigs.h"
#include "localplayer.h"
#include "gamesession.h"


DefaultEngineConfig::DefaultEngineConfig(GameSession& AssignedSession, LocalPlayer& AssignedPlayer)
	:	InputConfig(AssignedSession, AssignedPlayer)
{
}

DefaultEngineConfig::DefaultEngineConfig(GameSession& AssignedSession)
	:	InputConfig(AssignedSession)
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
		Session->GameOver();
		break;

	default:
		break;
	}
}