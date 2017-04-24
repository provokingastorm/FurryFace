#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftplayership.h"
#include "papercraftgameconfig.h"

#include "world2d.h"
#include "scene2dobject.h"
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

	PapercraftGameConfig& PapercraftInput = *(new PapercraftGameConfig(*Ship));
	InputSubsystem::Instance().PushConfig(PapercraftInput);
}

// EOF
