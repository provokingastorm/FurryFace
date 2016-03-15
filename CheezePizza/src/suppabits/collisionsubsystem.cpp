#include "cheezepizza.h"
#include "collisionsubsystem.h"
#include "collisioncomponent.h"
#include "cheezepizzaengine.h"

// ----------------------------------------------------------------------------
// CollisionSubsystem - Definition
// ----------------------------------------------------------------------------

int CollisionSubsystem::NextCollisionID = 0;

void CollisionSubsystem::InitializeInternal()
{
}

void CollisionSubsystem::ShutdownInternal()
{
}

void CollisionSubsystem::Tick(float DeltaTime)
{
}

int CollisionSubsystem::AddCollisionComponent(CollisionComponent* InComponent)
{
	int ID = INVALID_COL_INDEX;

	if(InComponent != NULL)
	{
		InComponent->ID = NextCollisionID;
		NextCollisionID++;

		if( InComponent->Callback != NULL && (InComponent->ResponseFlags & COLLISION_DisableOnRegistration) != 0 )
		{
			// TODO: Disable primitive here (put in a different list or append to back?)

			InComponent->bIsActive = false;
			InComponent->Callback->OnDisabledOnRegistration();
		}
	}

	return ID;
}

bool CollisionSubsystem::RemoveCollisionComponent(int InID)
{
	return false;
}

void CollisionSubsystem::CheckForCollisions(float DeltaTime)
{
}

// EOF
