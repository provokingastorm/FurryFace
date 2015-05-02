#include "cheezepizza.h"
#include "playerfactory.h"
#include "hud.h"
#include "localplayer.h"


// ----------------------------------------------------------------------------
// PlayerFactory - Definition
// ----------------------------------------------------------------------------

PlayerFactory::PlayerFactory()
{
}

PlayerFactory::~PlayerFactory()
{
}

LocalPlayer* PlayerFactory::CreateNewPlayer()
{
	LocalPlayer* NewPlayer = CreatePlayer();
	CPAssert(NewPlayer != NULL, "CreatePlayer() did not create a valid player");

	Hud* PlayerHud = CreateHud();
	CPAssert(PlayerHud != NULL, "CreateHud() did not create a valid HUD");

	NewPlayer->SetHUD(*PlayerHud);

	return NewPlayer;
}

LocalPlayer* PlayerFactory::CreatePlayer()
{
	CPAssert(true == false, "No implementation of CreatePlayer() provided for derived PlayerFactory");
	return NULL;
}

Hud* PlayerFactory::CreateHud()
{
	CPAssert(true == false, "No implementation of CreateHud() provided for derived PlayerFactory");
	return NULL;
}
