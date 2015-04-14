#include "cheezepizza.h"
#include "sharedrenderables.h"
#include "hgesprite.h"
#include "hgeanim.h"


AnimatedCharacter::AnimatedCharacter()
	: CurrentAnim(NULL)
{
}

AnimatedCharacter::~AnimatedCharacter()
{
	CurrentAnim = NULL;
}

void AnimatedCharacter::AddAnimation(hgeAnimation& InAnim)
{
	CurrentAnim = &InAnim;
}

void AnimatedCharacter::Tick(float DeltaTime)
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Update(DeltaTime);
	}
}

void AnimatedCharacter::Render(class HGE& Engine)
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Render(200, 200);
	}
}

void AnimatedCharacter::OnStart()
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Play();
	}
}

void AnimatedCharacter::OnStop()
{
}

void AnimatedCharacter::OnPause()
{
}




FullscreenBackground::FullscreenBackground()
	: Background(NULL)
{
}

FullscreenBackground::~FullscreenBackground()
{
	Background = NULL;
}

void FullscreenBackground::SetContent(hgeSprite& InBackground)
{
	Background = &InBackground;
}

void FullscreenBackground::Tick(float DeltaTime)
{
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

void FullscreenBackground::OnStart()
{
}

void FullscreenBackground::OnStop()
{
}

void FullscreenBackground::OnPause()
{
}