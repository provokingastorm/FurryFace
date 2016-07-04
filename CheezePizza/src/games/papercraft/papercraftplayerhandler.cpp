#include "cheezepizza.h"
#include "papercraftplayerhandler.h"

PapercraftPlayerHandler::PapercraftPlayerHandler()
{
}

PapercraftPlayerHandler::~PapercraftPlayerHandler()
{
	Ship = NULL;
}

void PapercraftPlayerHandler::SetShip(class PapercraftPlayerShip& InShip)
{
	Ship = &InShip;
}

// EOF
