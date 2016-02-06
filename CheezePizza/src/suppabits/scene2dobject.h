#ifndef Scene2DObject_H_
#define Scene2DObject_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif


// ----------------------------------------------------------------------------
// Scene2DObject - Declaration
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
	void SetComponentData(class ComponentData& InData);
	bool CanRender() const;

	// --------------------------------------------------------
	//	Tickable Methods

	virtual void Tick(float DeltaTime);

	virtual void Start();
	virtual void Stop();
	virtual void Pause();

private:

	class IRenderable* RenderObject;
	class ComponentData* OwnerData;
};


// ----------------------------------------------------------------------------
// Scene2DObject - Inline Methods
// ----------------------------------------------------------------------------

inline class IRenderable* Scene2DObject::GetRenderObject() const
{
	return RenderObject;
}

#endif

// EOF
