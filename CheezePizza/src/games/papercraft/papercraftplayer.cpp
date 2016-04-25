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
	// These object lifetimes are managed by World2D
	Ship = NULL;
}

void PapercraftPlayer::OnCreatedInternal()
{
	Ship = new PapercraftPlayerShip();
	World2D::Instance().AddPersistentObject(*Ship, SOL_Foreground);

	//InputCoodinator = new PlayerInputCoordinator(*Ship);
	//World2D::Instance().AddTickObject(*InputCoodinator);
}

// EOF
