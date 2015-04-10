#include "cheezepizza.h"
#include "playerfactory.h"
#include "hud.h"
#include "localplayer.h"


PlayerFactory::PlayerFactory(GameSession& AssignedSession)
	: Session(&AssignedSession)
{
}

PlayerFactory::PlayerFactory()
	: Session(NULL)
{
}

PlayerFactory::~PlayerFactory()
{
	Session = NULL;
}

LocalPlayer* PlayerFactory::CreateNewPlayer()
{
	CPAssert(Session != NULL, "No session was given to the player factory!");

	LocalPlayer* NewPlayer = CreatePlayer();
	CPAssert(NewPlayer != NULL, "CreatePlayer() did not create a valid player");

	Hud* PlayerHud = CreateHud();
	CPAssert(PlayerHud != NULL, "CreateHud() did not create a valid HUD");

	NewPlayer->SetHUD(*PlayerHud);
	NewPlayer->AssignToSession(*Session);

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
