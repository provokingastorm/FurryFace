#ifndef OriginsLinkRenderObject_H_
#define OriginsLinkRenderObject_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

class OriginsLinkRenderObject : public IRenderable
{
public:
	OriginsLinkRenderObject();
	~OriginsLinkRenderObject();

	void SetContent(class hgeSprite& InLinkSprite);
	void Render(class HGE& Engine);

private:
	hgeSprite* LinkSprite;
};

#endif