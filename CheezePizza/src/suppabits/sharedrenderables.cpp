#include "cheezepizza.h"
#include "sharedrenderables.h"
#include "cheezepizzaengine.h"
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




StaticImage::StaticImage()
	: Image(NULL)
	, HotSpot(0.0f, 0.0f)
{
}

StaticImage::~StaticImage()
{
	Image = NULL;
}

void StaticImage::SetContent(hgeSprite& InBackground)
{
	Image = &InBackground;
	Image->GetHotSpot(&HotSpot.X, &HotSpot.Y);
}

void StaticImage::Tick(float DeltaTime)
{
}

void StaticImage::Render(HGE& Engine)
{
	if(Image != NULL)
	{
		Image->RenderEx( HotSpot.X, HotSpot.Y, Rotation);
	}
}

void StaticImage::SetHotSpot(float X, float Y)
{
	HotSpot.X = X;
	HotSpot.Y = Y;
}

void StaticImage::OnStart()
{
}

void StaticImage::OnStop()
{
}

void StaticImage::OnPause()
{
}

// EOF
