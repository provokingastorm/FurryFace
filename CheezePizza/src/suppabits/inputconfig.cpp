#include "cheezepizza.h"
#include "inputconfig.h"
#include "inputcoordinator.h"

// ----------------------------------------------------------------------------
// InputConfig - Definition
// ----------------------------------------------------------------------------

InputConfig::InputConfig()
	: Coordinator(NULL)
{
}

InputConfig::InputConfig(InputCoordinator& InCoordinator)
	: Coordinator(&InCoordinator)
{
}

InputConfig::~InputConfig()
{
}

// EOF
