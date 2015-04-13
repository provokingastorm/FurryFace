#ifndef SharedRenderables_H_
#define SharedRenderables_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

class AnimatedCharacter : public IRenderable
{
public:
	AnimatedCharacter();
	~AnimatedCharacter();

	void AddAnimation(class hgeAnimation& InAnim);
	void Tick(float DeltaTime);
	void Render(class HGE& Engine);

private:
	class hgeAnimation* CurrentAnim;
};

class FullscreenBackground : public IRenderable
{
public:
	FullscreenBackground();
	~FullscreenBackground();

	void SetContent(class hgeSprite& InBackground);
	void Tick(float DeltaTime);
	void Render(class HGE& Engine);

private:
	class hgeSprite* Background;
};

#endif