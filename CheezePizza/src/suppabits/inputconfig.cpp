#include "cheezepizza.h"
#include "inputconfig.h"
#include "gamesession.h"
#include "localplayer.h"

InputConfig::InputConfig(GameSession& AssignedSession, LocalPlayer& AssignedPlayer)
	: Session(&AssignedSession)
	, Player(&AssignedPlayer)
{
}

InputConfig::InputConfig(GameSession& AssignedSession)
	: Session(&AssignedSession)
	, Player(NULL)
{
}

InputConfig::InputConfig()
	: Session(NULL)
	, Player(NULL)
{
}

InputConfig::~InputConfig()
{
}