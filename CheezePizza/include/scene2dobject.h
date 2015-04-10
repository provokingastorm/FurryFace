#ifndef Scene2DObject_H_
#define Scene2DObject_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif


// ----------------------------------------------------------------------------
// Purpose: 
// ----------------------------------------------------------------------------

class Scene2DObject : public Tickable
{
public:
	Scene2DObject();
	virtual ~Scene2DObject();


	// --------------------------------------------------------
	//	Rendering Methods

	class IRenderable* GetRenderObject() const;
	void SetRenderObject(class IRenderable& Object);
	bool CanRender() const;

private:
	class IRenderable* RenderObject;
};


// ----------------------------------------------------------------------------
// Scene2DObject - Inline Methods
// ----------------------------------------------------------------------------

inline class IRenderable* Scene2DObject::GetRenderObject() const
{
	return RenderObject;
}

#endif