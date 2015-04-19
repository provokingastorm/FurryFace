#include "cheezepizza.h"
#include "originslinkrenderobject.h"
#include "hgesprite.h"

OriginsLinkRenderObject::OriginsLinkRenderObject()
	: LinkSprite(NULL)
{
}

OriginsLinkRenderObject::~OriginsLinkRenderObject()
{
	LinkSprite = NULL;
}

void OriginsLinkRenderObject::SetContent(hgeSprite& InLinkSprite)
{
	LinkSprite = &InLinkSprite;
}

void OriginsLinkRenderObject::Render(HGE& Engine)
{
	if(LinkSprite != NULL)
	{
		LinkSprite->Render(320, 240);
	}
}