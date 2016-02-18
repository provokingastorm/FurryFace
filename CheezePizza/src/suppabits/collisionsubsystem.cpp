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

CollisionID CollisionSubsystem::AddCollisionPrimitive(hgeRect& InRect, class CollisionCallback* InCallback, DWORD InCollisionFlags)
{
	CollisionID ID = INVALID_COL_INDEX;

	if(InCallback != NULL)
	{
		CollisionEntry Entry;
		Entry.Bounds = InRect;
		Entry.Callback = InCallback;
		Entry.Flags = InCollisionFlags;

		// TODO: Set collision ID here

		if( (Entry.Flags & COLLISIONACTION_DisableOnRegistration) != 0 )
		{
			// TODO: Disable entry here

			Entry.Callback->OnDisabled();
		}
	}

	return ID;
}

// EOF
