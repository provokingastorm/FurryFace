#include "cheezepizza.h"
#include "inputconfig.h"
#include "inputhandler.h"

// ----------------------------------------------------------------------------
// InputConfig - Definition
// ----------------------------------------------------------------------------

InputConfig::InputConfig()
	: Handler(NULL)
{
}

InputConfig::InputConfig(InputHandler& InHandler)
	: Handler(&InHandler)
{
}

InputConfig::~InputConfig()
{
}

// EOF
