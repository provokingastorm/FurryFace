#ifndef ScreenPartition_H_
#define ScreenPartition_H_

#ifndef HGERECT_H
#include "hgerect.h"
#endif


// ----------------------------------------------------------------------------
// ScreenPartition - Defines
// ----------------------------------------------------------------------------

#define INVALID_PARTITION_ID	-1

// ----------------------------------------------------------------------------
// ScreenPartition - Declaration
// ----------------------------------------------------------------------------

class ScreenPartition
{
public:

	ScreenPartition();
	~ScreenPartition();

	void RecalculateBounds(class hgeRect& InBounds, int InRows, int InColumns);
	int GetPartitionIDForPoint(float ScreenPointX, float ScreenPointY) const;

private:

	hgeRect* Partitions;
	hgeRect Bounds;

	int RowSize;
	int ColumnSize;

	float PartitionWidth;
	float PartitionHeight;
};

#endif

// EOF
