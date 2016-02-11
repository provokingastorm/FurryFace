#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftplayership.h"


// ----------------------------------------------------------------------------
// PapercraftPlayer - Definition
// ----------------------------------------------------------------------------

PapercraftPlayer::PapercraftPlayer()
{
}

PapercraftPlayer::~PapercraftPlayer()
{
	if(Ship != NULL)
	{
		delete Ship;
		Ship = NULL;
	}
}

void PapercraftPlayer::OnCreatedInternal()
{
	Ship = new PapercraftPlayerShip();
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveUp(DeltaTime);
	}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveDown(DeltaTime);
	}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveLeft(DeltaTime);
	}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	if(Ship != NULL)
	{
		Ship->MoveRight(DeltaTime);
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
