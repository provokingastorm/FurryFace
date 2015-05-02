#include "cheezepizza.h"
#include "win32platform.h"

Win32Platform::Win32Platform()
{
	HGEEngine = hgeCreate(HGE_VERSION);
}

Win32Platform::~Win32Platform()
{
	// If there are no more references, the HGE object will be deleted.
	HGEEngine->Release();
	HGEEngine = NULL;
}

HGE* Win32Platform::GetHGE() const
{
	return HGEEngine;
}

hgeResourceManager* Win32Platform::GetResourceManager() const
{
	return ResourceManager;
}
