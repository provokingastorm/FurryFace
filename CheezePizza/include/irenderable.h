#ifndef IRenderable_H_
#define IRenderable_H_

class IRenderable
{
public:
	virtual void Render(class HGE& Engine) = 0;
};

#endif