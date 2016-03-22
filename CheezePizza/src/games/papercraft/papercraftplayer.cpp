#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftplayership.h"

#include "world2d.h"


// ----------------------------------------------------------------------------
// PapercraftPlayer - Definition
// ----------------------------------------------------------------------------

PapercraftPlayer::PapercraftPlayer()
{
}

PapercraftPlayer::~PapercraftPlayer()
{
	// The ship's lifetime is managed by World2D
	Ship = NULL;
}

void PapercraftPlayer::OnCreatedInternal()
{
	Ship = new PapercraftPlayerShip();
	World2D::Instance().AddPersistentObject(*Ship, SOL_Foreground);
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveVertical(1.0f);
	}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveVertical(-1.0f);
	}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveHorizontal(-1.0f);
	}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveHorizontal(1.0f);
	}
}

void PapercraftPlayer::ResetVelocity()
{
	if(Ship != NULL)
	{
		Ship->ResetVelocity();
	}
}

void PapercraftPlayer::FirePrimaryWeapon(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->FirePrimaryWeapon(DeltaTime);
	}
}

// EOF
