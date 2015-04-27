#include "cheezepizza.h"
#include "inputconfig.h"
#include "localplayer.h"

InputConfig::InputConfig()
	: Player(NULL)
{
}

InputConfig::InputConfig(LocalPlayer& AssignedPlayer)
	: Player(&AssignedPlayer)
{
}

InputConfig::~InputConfig()
{
}