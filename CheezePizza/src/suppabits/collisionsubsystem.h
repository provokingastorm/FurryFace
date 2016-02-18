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
#define	COLLISIONACTION_None					0x00000000
/* Remove the entry from the collision result when a collision occurs */
#define	COLLISIONACTION_RemoveOnCollision		0x00000001
/* Disable the entry in the collision system when a collision occurs */
#define	COLLISIONACTION_DisableOnCollision		0x00000002
/* Automatically disables the entry when first registered with the system */
#define COLLISIONACTION_DisableOnRegistration	0x00000004
/* Do everything */
#define	COLLISIONACTION_All						0xFFFFFFFF

// ----------------------------------------------------------------------------
// CollisionSubsystem - Typedefs
// ----------------------------------------------------------------------------

typedef int CollisionID;

// ----------------------------------------------------------------------------
// CollisionSubsystem - Structs
// ----------------------------------------------------------------------------

struct CollisionEntry
{
	CollisionID ID;
	class CollisionCallback* Callback;
	DWORD Flags;
	hgeRect Bounds;
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
	virtual void OnEnabled()	{}
	virtual void OnDisabled()	{}
	virtual void OnRemoved()	{}
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
	//	CollisionSubsystem public methods

	CollisionID AddCollisionPrimitive(hgeRect& InRect, class CollisionCallback* InCallback, DWORD InCollisionFlags);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

};

#endif

// EOF
