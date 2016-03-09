#include "cheezepizza.h"
#include "screenpartition.h"


// ----------------------------------------------------------------------------
// ScreenPartition - Definition
// ----------------------------------------------------------------------------

ScreenPartition::ScreenPartition()
{
	memset(ChildPartitions, 0, 4 * PARTITION_SIZE);
}

ScreenPartition::~ScreenPartition()
{
	DeleteChildren();
}

void ScreenPartition::AddChildren(hgeRect& InBounds, int SubLevels)
{
	Bounds = InBounds;

	if(SubLevels > 0)
	{
		SubLevels -= 1;

		const float PartitionDivisor = 0.25f;
		const float CellSizeX = (Bounds.x2 - Bounds.x1) * PartitionDivisor;
		const float CellSizeY = (Bounds.y2 - Bounds.y1) * PartitionDivisor;

		// Top-left cell partition
		hgeRect Bounds1;
		Bounds1.x1 = InBounds.x1;
		Bounds1.x2 = InBounds.x1 + CellSizeX;
		Bounds1.y1 = InBounds.y1;
		Bounds1.y2 = InBounds.y1 + CellSizeY;

		ChildPartitions[0] = new ScreenPartition();
		ChildPartitions[0]->AddChildren(Bounds1, SubLevels);

		// Top-right cell partition
		hgeRect Bounds2;
		Bounds2.x1 = Bounds1.x2;
		Bounds2.x2 = Bounds2.x1 + CellSizeX;
		Bounds2.y1 = Bounds1.y1;
		Bounds2.y2 = Bounds1.y2;

		ChildPartitions[1] = new ScreenPartition();
		ChildPartitions[1]->AddChildren(Bounds2, SubLevels);

		// Bottom-left cell partition
		hgeRect Bounds3;
		Bounds3.x1 = Bounds1.x1;
		Bounds3.x2 = Bounds1.x2;
		Bounds3.y1 = Bounds1.y2;
		Bounds3.y2 = Bounds3.y1 + CellSizeY;

		ChildPartitions[2] = new ScreenPartition();
		ChildPartitions[2]->AddChildren(Bounds3, SubLevels);

		// Bottom-right cell partition
		hgeRect Bounds4;
		Bounds4.x1 = Bounds2.x1;
		Bounds4.x2 = Bounds2.x2;
		Bounds4.y1 = Bounds3.y1;
		Bounds4.y2 = Bounds3.y2;

		ChildPartitions[3] = new ScreenPartition();
		ChildPartitions[3]->AddChildren(Bounds4, SubLevels);
	}
}

void ScreenPartition::DeleteChildren()
{
	for(int Index = 0; Index < PARTITION_SIZE; Index++)
	{
		if(ChildPartitions[Index] != 0)
		{
			ChildPartitions[Index]->DeleteChildren();
			delete ChildPartitions[Index];
			ChildPartitions[Index] = NULL;
		}
	}
}

// EOF
