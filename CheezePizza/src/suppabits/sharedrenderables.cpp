#include "cheezepizza.h"
#include "sharedrenderables.h"
#include "hgesprite.h"

FullscreenBackground::FullscreenBackground()
	: Background(NULL)
{
}

FullscreenBackground::~FullscreenBackground()
{
}

void FullscreenBackground::SetContent(hgeSprite& InBackground)
{
	Background = &InBackground;
}

void FullscreenBackground::Render(HGE& Engine)
{
	if(Background != NULL)
	{
		float HotspotX, HotspotY = 0;
		Background->GetHotSpot(&HotspotX, &HotspotY);
		Background->Render(HotspotX, HotspotY);
	}
}