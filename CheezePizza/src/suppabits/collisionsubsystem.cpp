#include "cheezepizza.h"
#include "collisionsubsystem.h"


// ----------------------------------------------------------------------------
// ScreenPartition - Defines
// ----------------------------------------------------------------------------

#define PARTITION_SETS	2
/* Should be a multiple of 2! */
#define PARTITION_SIZE	4


// ----------------------------------------------------------------------------
// ScreenPartition - Declaration
// ----------------------------------------------------------------------------

class ScreenPartition
{
public:

	void SetChildPartition(int Index, ScreenPartition* Partition);
	void AddChildren(hgeRect& InBounds, int Children);

private:
	
	ScreenPartition* ChildPartitions[PARTITION_SIZE];
	hgeRect Bounds;
};


// ----------------------------------------------------------------------------
// ScreenPartition - Definition
// ----------------------------------------------------------------------------

void ScreenPartition::SetChildPartition(int Index, ScreenPartition* Partition)
{
	if(Partition != NULL && Index >= 0 && Index < PARTITION_SIZE)
	{
		ChildPartitions[Index] = Partition;
	}
}

void ScreenPartition::AddChildren(hgeRect& InBounds, int Children)
{
	Bounds = InBounds;

	for(int Index = 0; Index < PARTITION_SETS; Index++)
	{
		const float PartitionDivisor = 0.25f;
		const float PartitionSizeX = (Bounds.x2 - Bounds.x1) * PartitionDivisor;
		const float PartitionSizeY = (Bounds.y2 - Bounds.y1) * PartitionDivisor;

		hgeRect Bounds1;
		Bounds1.x1 = Bounds.x1;
		Bounds1.x2 = Bounds.x1 + PartitionSizeX;
		Bounds1.y1 = Bounds.y1;
		Bounds1.y2 = Bounds.y1 + PartitionSizeY;

		hgeRect Bounds2;
	}
}


// ----------------------------------------------------------------------------
// CollisionSubsystem - Definition
// ----------------------------------------------------------------------------

void CollisionSubsystem::InitializeInternal()
{
}

void CollisionSubsystem::ShutdownInternal()
{
}

void CollisionSubsystem::Tick(float DeltaTime)
{
}

CollisionID CollisionSubsystem::AddCollisionComponent(CollisionComponent* InComponent)
{
	CollisionID ID = INVALID_COL_INDEX;

	if(InComponent != NULL)
	{
		// TODO: Set collision ID here
		InComponent->ID = INVALID_COL_INDEX;

		if(InComponent->Callback != NULL && (InComponent->ResponseFlags & COLLISION_DisableOnRegistration) != 0 )
		{
			// TODO: Disable primitive here

			InComponent->Callback->OnDisabledOnRegistration();
		}
	}

	return ID;
}

bool CollisionSubsystem::RemoveCollisionComponent(CollisionID InID)
{
	return false;
}

void CollisionSubsystem::CheckForCollisions(float DeltaTime)
{

}

void AddFourSubPartitions(ScreenPartition& Parent)
{
	for(int Index = 0; Index < 4; Index++)
	{
		ScreenPartition* Child = new ScreenPartition();
		Parent.SetChildPartition(Index, Child);
	}
}

void CollisionSubsystem::SetScreenBounds(const hgeRect& InScreenBounds)
{
	ScreenBounds = InScreenBounds;

	if(HeadPartition == NULL)
	{
		HeadPartition = new ScreenPartition();
	}

	HeadPartition->AddChildren(ScreenBounds, 2);
}

// EOF
