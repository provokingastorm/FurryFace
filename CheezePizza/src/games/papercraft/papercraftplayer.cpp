#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftplayership.h"
#include "papercraftplayerhandler.h"
#include "papercraftgameconfig.h"

#include "world2d.h"
#include "inputsubsystem.h"


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
	// TODO Do we really need to save a reference to this object if World2D is managing it?
	Ship = new PapercraftPlayerShip();
	World2D::Instance().AddPersistentObject(*Ship, SOL_Foreground);

	PapercraftPlayerHandler& Handler = *(new PapercraftPlayerHandler());
	Handler.SetShip(*Ship);
	World2D::Instance().AddTickObject(Handler);

	PapercraftGameConfig& PapercraftInput = *(new PapercraftGameConfig(Handler));
	InputSubsystem::Instance().PushConfig(PapercraftInput);
}

// EOF
