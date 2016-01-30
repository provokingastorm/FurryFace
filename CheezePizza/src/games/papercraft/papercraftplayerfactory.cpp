#include "cheezepizza.h"
#include "papercraftplayerfactory.h"
#include "papercrafthud.h"
#include "papercraftplayer.h"


PapercraftPlayerFactory::PapercraftPlayerFactory()
	: PlayerFactory()
{
}

LocalPlayer* PapercraftPlayerFactory::CreatePlayer()
{
	return new PapercraftPlayer();
}

Hud* PapercraftPlayerFactory::CreateHud()
{
	return new PapercraftHud();
}

// EOF
