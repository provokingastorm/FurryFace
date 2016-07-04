#include "cheezepizza.h"
#include "inputconfig.h"
#include "actionhandler.h"

// ----------------------------------------------------------------------------
// InputConfig - Definition
// ----------------------------------------------------------------------------

InputConfig::InputConfig()
	: Handler(NULL)
{
}

InputConfig::InputConfig(ActionHandler& InHandler)
	: Handler(&InHandler)
{
}

InputConfig::~InputConfig()
{
}

// EOF
