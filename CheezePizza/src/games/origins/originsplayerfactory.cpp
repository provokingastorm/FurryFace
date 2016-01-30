#include "cheezepizza.h"
#include "originsplayerfactory.h"
#include "originshud.h"
#include "originsplayer.h"


OriginsPlayerFactory::OriginsPlayerFactory()
	: PlayerFactory()
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

// EOF
