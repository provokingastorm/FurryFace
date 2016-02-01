#include "cheezepizza.h"
#include "sharedrenderables.h"
#include "hgesprite.h"
#include "hgeanim.h"


AnimatedCharacter::AnimatedCharacter()
	: CurrentAnim(NULL)
	, HotSpot(0.0f, 0.0f)
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
		CurrentAnim->Render(HotSpot.X, HotSpot.Y);
	}
}

void AnimatedCharacter::SetHotSpot(float X, float Y)
{
	HotSpot.X = X;
	HotSpot.Y = Y;
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
	, HotSpot(0.0f, 0.0f)
{
}

FullscreenBackground::~FullscreenBackground()
{
	Background = NULL;
}

void FullscreenBackground::SetContent(hgeSprite& InBackground)
{
	Background = &InBackground;
	Background->GetHotSpot(&HotSpot.X, &HotSpot.Y);
}

void FullscreenBackground::Tick(float DeltaTime)
{
}

void FullscreenBackground::Render(HGE& Engine)
{
	if(Background != NULL)
	{
		Background->Render(HotSpot.X, HotSpot.Y);
	}
}

void FullscreenBackground::SetHotSpot(float X, float Y)
{
	HotSpot.X = X;
	HotSpot.Y = Y;
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

// EOF
