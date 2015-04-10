#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "gamesession.h"
#include "localplayer.h"

OriginsGameConfig::OriginsGameConfig(GameSession& AssignedSession, LocalPlayer& AssignedPlayer)
	: InputConfig(AssignedSession, AssignedPlayer)
{
}

OriginsGameConfig::OriginsGameConfig(GameSession& AssignedSession)
	: InputConfig(AssignedSession)
{
}

OriginsGameConfig::~OriginsGameConfig()
{
}

void OriginsGameConfig::GetKeyUpEvents(std::vector<int>& KeyUpEvents)
{
	KeyUpEvents.push_back(HGEK_ESCAPE);
}

void OriginsGameConfig::OnKeyUp(int KeyID)
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