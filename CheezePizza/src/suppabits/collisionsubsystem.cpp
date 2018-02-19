#include "cheezepizza.h"
#include "collisionsubsystem.h"
#include "cheezepizzaengine.h"

// ----------------------------------------------------------------------------
// CollisionSubsystem - Definition
// ----------------------------------------------------------------------------

void CollisionSubsystem::InitializeInternal()
{
	FirstFreeCompIndex = 0;

	for(int i = 0; i < MAX_COLLISION_COMPONENTS; i++)
	{
		Components[i].Reset();
		Components[i].ID = i;
	}
}

void CollisionSubsystem::ShutdownInternal()
{
}

void CollisionSubsystem::Tick(float DeltaTime)
{
}

CollisionComponent* CollisionSubsystem::CreateCollisionComponent()
{
	CollisionComponent* NewComponent = NULL;

	// Only create a new collision component if we haven't reached the max
	if(FirstFreeCompIndex < (MAX_COLLISION_COMPONENTS-1))
	{
		NewComponent = &Components[FirstFreeCompIndex];
		FirstFreeCompIndex += 1;
	}

	return NewComponent;
}

bool CollisionSubsystem::RemoveCollisionComponent(CollisionComponent* InComponent)
{
	bool bWasRemoved = false;

	if(InComponent != NULL && InComponent->ID >= 0 && InComponent->ID < MAX_COLLISION_COMPONENTS)
	{
		// "Remove" the component by swapping the component with the last valid component in the array

		const int ToRemoveID = InComponent->ID;
		const int LastValidID = FirstFreeCompIndex - 1;

		// Perform the component swap
		Components[ToRemoveID] = Components[LastValidID];

		// Update the ID of the valid component since we moved its position in the array
		Components[ToRemoveID].ID = ToRemoveID;

		// Don't bother copying the "removed" component. Since we're freeing it, just clear out the existing 
		Components[LastValidID].Reset();

		// Update the index pointer to the new first free component
		FirstFreeCompIndex = LastValidID;
	}

	return bWasRemoved;
}

void CollisionSubsystem::CheckForCollisions(float DeltaTime)
{
}

// EOF
