#include "cheezepizza.h"
#include "inputconfig.h"
#include "localplayer.h"

InputConfig::InputConfig()
	: Player(NULL)
	, CachedDeltaTime(0.0f)
{
}

InputConfig::InputConfig(LocalPlayer& AssignedPlayer)
	: Player(&AssignedPlayer)
{
}

InputConfig::~InputConfig()
{
}

void InputConfig::SetDeltaTime(float DeltaTime)
{
	CachedDeltaTime = DeltaTime;
}