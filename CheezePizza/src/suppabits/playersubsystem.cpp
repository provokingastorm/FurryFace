#include "cheezepizza.h"
#include "playersubsystem.h"
#include "playerfactory.h"
#include "localplayer.h"
#include "cheezepizzaengine.h"


void PlayerSubsystem::InitializeInternal()
{
	PlayerCreator = NULL;

	for(int i = 0; i < MAX_LOCAL_PLAYERS; ++i)
	{
		Players[i] = NULL;
	}
}

void PlayerSubsystem::ShutdownInternal()
{
	SAFE_DELETE(PlayerCreator);

	for(int i = 0; i < MAX_LOCAL_PLAYERS; ++i)
	{
		SAFE_DELETE(Players[i]);
	}
}

void PlayerSubsystem::OnFirstEngineTick()
{
	SetupNewLocalPlayer(LPI_PlayerOne);
}

void PlayerSubsystem::SetPlayerFactory(PlayerFactory& Factory)
{
	PlayerCreator = &Factory;
}

bool PlayerSubsystem::IsLocalPlayerLoggedIn(ELocalPlayerIndex PlayerIndex) const
{
	return Players[PlayerIndex] != NULL;
}

void PlayerSubsystem::SetupNewLocalPlayer(ELocalPlayerIndex PlayerIndex)
{
	if(PlayerCreator != NULL && !IsLocalPlayerLoggedIn(PlayerIndex))
	{
		LocalPlayer* Player = PlayerCreator->CreateNewPlayer();

		if(Player != NULL)
		{
			Players[PlayerIndex] = Player;
		}

		Player->OnCreated();
	}
}