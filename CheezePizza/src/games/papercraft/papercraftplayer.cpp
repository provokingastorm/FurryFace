#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftplayership.h"

#include "world2d.h"


// ----------------------------------------------------------------------------
// PlayerInputCoordinator - Declaration
// ----------------------------------------------------------------------------

class PlayerInputCoordinator : public Tickable
{
public:

	PlayerInputCoordinator(PapercraftPlayerShip& InShip);

private:

	PlayerInputCoordinator();

	void PreTick(float DeltaTime);

	PapercraftPlayerShip& Ship;
};


// ----------------------------------------------------------------------------
// PlayerInputCoordinator - Definition
// ----------------------------------------------------------------------------

PlayerInputCoordinator::PlayerInputCoordinator(PapercraftPlayerShip& InShip)
	: Ship(InShip)
{
	SetTickType(ETT_PreTick);
}

void PlayerInputCoordinator::PreTick(float DeltaTime)
{
}


// ----------------------------------------------------------------------------
// PapercraftPlayer - Definition
// ----------------------------------------------------------------------------

PapercraftPlayer::PapercraftPlayer()
{
}

PapercraftPlayer::~PapercraftPlayer()
{
	// These object lifetimes are managed by World2D
	Ship = NULL;
	InputCoodinator = NULL;
}

void PapercraftPlayer::OnCreatedInternal()
{
	Ship = new PapercraftPlayerShip();
	World2D::Instance().AddPersistentObject(*Ship, SOL_Foreground);

	InputCoodinator = new PlayerInputCoordinator(*Ship);
	World2D::Instance().AddTickObject(*InputCoodinator);
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->MoveVertical(1.0f);
	//}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->MoveVertical(-1.0f);
	//}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->MoveHorizontal(-1.0f);
	//}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->MoveHorizontal(1.0f);
	//}
}

void PapercraftPlayer::ResetVelocity()
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->ResetVelocity();
	//}
}

void PapercraftPlayer::FirePrimaryWeapon(float DeltaTime)
{
	//if(InputCoodinator != NULL)
	//{
		//InputCoodinator->FirePrimaryWeapon(DeltaTime);
	//}
}

// EOF
