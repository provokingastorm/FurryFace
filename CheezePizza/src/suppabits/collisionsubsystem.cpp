#include "cheezepizza.h"
#include "collisionsubsystem.h"

void CollisionSubsystem::InitializeInternal()
{
}

void CollisionSubsystem::ShutdownInternal()
{
}

void CollisionSubsystem::Tick(float DeltaTime)
{
}

CollisionID CollisionSubsystem::AddCollisionPrimitive(hgeRect* InRect, class CollisionCallback* InCallback, DWORD InCollisionFlags)
{
	CollisionID ID = INVALID_COL_INDEX;

	if(InRect != NULL && InCallback != NULL)
	{
		CollisionPrimitive Primitive;
		Primitive.Bounds	= InRect;
		Primitive.Callback	= InCallback;
		Primitive.Flags		= InCollisionFlags;

		// TODO: Set collision ID here

		if( (Primitive.Flags & COLLISION_DisableOnRegistration) != 0 )
		{
			// TODO: Disable primitive here

			Primitive.Callback->OnDisabledOnRegistration();
		}
	}

	return ID;
}

bool CollisionSubsystem::RemoveCollisionPrimitive(CollisionID InID)
{
	return false;
}

void CollisionSubsystem::SetScreenBounds(const hgeRect& InScreenBounds)
{
	ScreenBounds = InScreenBounds;
}

// EOF
