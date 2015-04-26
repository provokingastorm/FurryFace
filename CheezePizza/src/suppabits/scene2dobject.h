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

	// --------------------------------------------------------
	//	Tickable Methods

	virtual void Tick(float DeltaTime);

	virtual void Start();
	virtual void Stop();
	virtual void Pause();

	int GetX() const;
	int GetY() const;

	void Move(int NewX, int NewY);
	void MoveVertical(int NewX);
	void MoveHorizontal(int NewY);

private:
	class IRenderable* RenderObject;

	int X;
	int Y;
};


// ----------------------------------------------------------------------------
// Scene2DObject - Inline Methods
// ----------------------------------------------------------------------------

inline class IRenderable* Scene2DObject::GetRenderObject() const
{
	return RenderObject;
}

inline int Scene2DObject::GetX() const
{
	return X;
}

inline int Scene2DObject::GetY() const
{
	return Y;
}

#endif