#ifndef SharedRenderables_H_
#define SharedRenderables_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

class FullscreenBackground : public IRenderable
{
public:
	FullscreenBackground();
	~FullscreenBackground();

	void SetContent(class hgeSprite& InBackground);
	void Render(class HGE& Engine);

private:
	hgeSprite* Background;
};

#endif