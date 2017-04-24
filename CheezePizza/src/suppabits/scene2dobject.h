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

	Scene2DObject(struct Scene2DObjectData& InData);
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

	Vector2D GetPosition() const;
	virtual bool MovedThisTick() const			{ return false; }

	virtual void RegisterCollisionComponent()	{}
	void SetPartition(int PartitionID);

	void QueueAction(int ActionType);

protected:

	Scene2DObject();
	virtual void OnSetPartitionID(int PartitionID) {}

	struct Scene2DObjectData& ObjectData;
};

#endif

// EOF
