#ifndef SharedRenderables_H_
#define SharedRenderables_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

#ifndef Vector2D_H_
#include "vector2d.h"
#endif

class AnimatedCharacter : public IRenderable
{
public:
	AnimatedCharacter();
	~AnimatedCharacter();

	void AddAnimation(class hgeAnimation& InAnim);

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void SetHotSpot(float X, float Y);
	void OnStart();
	void OnStop();
	void OnPause();

private:
	class hgeAnimation* CurrentAnim;
	Vector2D HotSpot;
};

class FullscreenBackground : public IRenderable
{
public:
	FullscreenBackground();
	~FullscreenBackground();

	void SetContent(class hgeSprite& InBackground);

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void SetHotSpot(float X, float Y);
	void OnStart();
	void OnStop();
	void OnPause();

private:
	class hgeSprite* Background;
	Vector2D HotSpot;
};

#endif

// EOF
