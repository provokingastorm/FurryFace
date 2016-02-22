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

// Collision channels
#define COLLISIONCHANNEL_None					0x00000000
#define COLLISIONCHANNEL_01						0x00000001
#define COLLISIONCHANNEL_02						0x00000010
#define COLLISIONCHANNEL_03						0x00000100
#define COLLISIONCHANNEL_04						0x00001000
#define COLLISIONCHANNEL_05						0x00010000
#define COLLISIONCHANNEL_06						0x00100000
#define COLLISIONCHANNEL_07						0x01000000
#define COLLISIONCHANNEL_08						0x10000000
#define COLLISIONCHANNEL_All					0x11111111

// ----------------------------------------------------------------------------
// CollisionSubsystem - Typedefs
// ----------------------------------------------------------------------------

typedef int CollisionID;

// ----------------------------------------------------------------------------
// CollisionCallback - Declaration
// ----------------------------------------------------------------------------

class CollisionCallback
{
public:

	CollisionCallback() {}
	~CollisionCallback() {}

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
// CollisionComponent - Declaration
// ----------------------------------------------------------------------------

class CollisionComponent
{
private:

	CollisionID ID;

public:

	CollisionComponent()
		: ID(INVALID_COL_INDEX)
		, bIsActive(false)
		, ChannelFlags(COLLISIONCHANNEL_None)
		, Bounds(hgeRect(0.0f, 0.0f, 0.0f, 0.0f))
		, Callback(NULL)
		, ResponseFlags(COLLISION_None)
	{
	}

	~CollisionComponent()
	{
		if(Callback != NULL)
		{
			delete Callback;
			Callback = NULL;
		}
	}

	CollisionID GetCollisionID() const { return ID; }

	bool bIsActive;
	DWORD ChannelFlags;
	hgeRect Bounds;
	class CollisionCallback* Callback;
	DWORD ResponseFlags;

	friend class CollisionSubsystem;
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

	CollisionID AddCollisionComponent(CollisionComponent* InComponent);
	bool RemoveCollisionComponent(CollisionID InID);

	void CheckForCollisions(float DeltaTime);

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
	class ScreenPartition* HeadPartition;

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
