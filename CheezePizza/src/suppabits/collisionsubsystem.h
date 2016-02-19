#ifndef CollisionSubsystem_H_
#define CollisionSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef HGERECT_H
#include "hgerect.h"
#endif

// ----------------------------------------------------------------------------
// CollisionSubsystem - Defines
// ----------------------------------------------------------------------------

#define INVALID_COL_INDEX	-1

// Collision Flags
#define	COLLISION_None							0x00000000
/* Remove the primitive from the collision result when a collision occurs */
#define	COLLISION_RemoveOnCollision				0x00000001
/* Remove the primitive from the collision system when its bounds is completely off-screen */
#define COLLISION_RemoveWhenOffScreen			0x00000002
/* Disable the primitive in the collision system when a collision occurs */
#define	COLLISION_DisableOnCollision			0x00000004
/* Automatically disables the entry when first registered with the system */
#define COLLISION_DisableOnRegistration			0x00000008
/* Do everything */
#define	COLLISIONACTION_All						0xFFFFFFFF

// ----------------------------------------------------------------------------
// CollisionSubsystem - Typedefs
// ----------------------------------------------------------------------------

typedef int CollisionID;

// ----------------------------------------------------------------------------
// CollisionSubsystem - Structs
// ----------------------------------------------------------------------------

struct CollisionPrimitive
{
	CollisionID ID;
	hgeRect* Bounds;
	class CollisionCallback* Callback;
	DWORD Flags;
};

// ----------------------------------------------------------------------------
// CollisionCallback - Declaration
// ----------------------------------------------------------------------------

class CollisionCallback
{
public:

	// Mandatory functionality
	virtual void OnCollision(const hgeRect& Other) = 0;

	// Optional functionality
	virtual void OnEnabled()				{}
	virtual void OnRemovedOnCollision()		{}
	virtual void OnRemovedOnOffScreen()		{}
	virtual void OnDisabledOnRegistration()	{}
	virtual void OnDisabledOnCollision()	{}
};


// ----------------------------------------------------------------------------
// CollisionSubsystem - Declaration
// ----------------------------------------------------------------------------

class CollisionSubsystem : public EngineSubsystem
{
public:

	DECLARE_SUBSYSTEM(CollisionSubsystem);

	// --------------------------------------------------------
	//	EngineSubsystem inherited public methods

	void Tick(float DeltaTime);

	// --------------------------------------------------------
	//	CollisionSubsystem registration public methods

	CollisionID AddCollisionPrimitive(hgeRect* InRect, class CollisionCallback* InCallback, DWORD InCollisionFlags);
	bool RemoveCollisionPrimitive(CollisionID InID);

	// --------------------------------------------------------
	//	Screen bounds public methods

	inline hgeRect GetScreenBounds() const;
	void SetScreenBounds(const hgeRect& InScreenBounds);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

private:

	hgeRect ScreenBounds;

};


// ----------------------------------------------------------------------------
// CollisionSubsystem - Declaration
// ----------------------------------------------------------------------------

hgeRect CollisionSubsystem::GetScreenBounds() const
{
	return ScreenBounds;
}

#endif

// EOF
