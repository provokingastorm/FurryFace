#include "cheezepizza.h"
#include "sharedinputconfigs.h"
#include "localplayer.h"
#include "cheezepizzaengine.h"

// ----------------------------------------------------------------------------
// DefaultEngineConfig - Definintion
// ----------------------------------------------------------------------------

DefaultEngineConfig::DefaultEngineConfig()
	:	InputConfig()
{
}

DefaultEngineConfig::DefaultEngineConfig(PlayerInputCoordinator& InCoordinator)
	:	InputConfig(InCoordinator)
{
}

DefaultEngineConfig::~DefaultEngineConfig()
{
}

// EOF
