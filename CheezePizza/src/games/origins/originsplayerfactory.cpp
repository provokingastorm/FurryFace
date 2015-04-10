#include "cheezepizza.h"
#include "originsplayerfactory.h"
#include "originshud.h"
#include "originsplayer.h"


OriginsPlayerFactory::OriginsPlayerFactory(GameSession& AssignedSession)
	: PlayerFactory(AssignedSession)
{
}

LocalPlayer* OriginsPlayerFactory::CreatePlayer()
{
	return new OriginsPlayer();
}

Hud* OriginsPlayerFactory::CreateHud()
{
	return new OriginsHud();
}