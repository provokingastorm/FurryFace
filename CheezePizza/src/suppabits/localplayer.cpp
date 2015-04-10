#include "cheezepizza.h"
#include "localplayer.h"
#include "gamesession.h"
#include "hud.h"

LocalPlayer::LocalPlayer()
	: GameHud(NULL)
	, Session(NULL)
{
}

LocalPlayer::~LocalPlayer()
{
	Session = NULL;

	if(GameHud != NULL)
	{
		delete GameHud;
	}
}

void LocalPlayer::SetHUD(Hud& NewHud)
{
	GameHud = &NewHud;
}

void LocalPlayer::AssignToSession(GameSession& NewSession)
{
	Session = &NewSession;
}

void LocalPlayer::OnCreated()
{
	if(Session != NULL)
	{
		Session->OnPlayerCreated(*this);
	}
}