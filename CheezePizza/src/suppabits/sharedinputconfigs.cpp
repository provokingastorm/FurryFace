#include "cheezepizza.h"
#include "sharedinputconfigs.h"
#include "localplayer.h"
#include "cheezepizzaengine.h"

DefaultEngineConfig::DefaultEngineConfig()
	:	InputConfig()
{
}

DefaultEngineConfig::DefaultEngineConfig(LocalPlayer& AssignedPlayer)
	:	InputConfig(AssignedPlayer)
{
}

DefaultEngineConfig::~DefaultEngineConfig()
{
}