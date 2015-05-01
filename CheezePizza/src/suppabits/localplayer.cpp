#include "cheezepizza.h"
#include "localplayer.h"
#include "hud.h"

LocalPlayer::LocalPlayer()
	: GameHud(NULL)
{
}

LocalPlayer::~LocalPlayer()
{
	SAFE_DELETE(GameHud);
}

void LocalPlayer::SetHUD(Hud& NewHud)
{
	GameHud = &NewHud;
}

void LocalPlayer::OnCreated()
{
	OnCreatedInternal();
}