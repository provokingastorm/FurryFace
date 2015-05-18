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
	void SetComponentSystem(class ComponentSystem& System);
	bool CanRender() const;

	// --------------------------------------------------------
	//	Tickable Methods

	virtual void Tick(float DeltaTime);

	virtual void Start();
	virtual void Stop();
	virtual void Pause();

	class ComponentData& GetData() const;

	float GetX() const;
	float GetY() const;

	void Move(float NewX, float NewY);
	void MoveVertical(float NewY);
	void MoveHorizontal(float NewX);

private:
	class IRenderable* RenderObject;
	class ComponentSystem* Components;
};


// ----------------------------------------------------------------------------
// Scene2DObject - Inline Methods
// ----------------------------------------------------------------------------

inline class IRenderable* Scene2DObject::GetRenderObject() const
{
	return RenderObject;
}

#endif