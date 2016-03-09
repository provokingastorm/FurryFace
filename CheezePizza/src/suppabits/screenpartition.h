#ifndef ScreenPartition_H_
#define ScreenPartition_H_

#ifndef HGERECT_H
#include "hgerect.h"
#endif

// ----------------------------------------------------------------------------
// ScreenPartition - Defines
// ----------------------------------------------------------------------------

/* Should be a multiple of 2! */
#define PARTITION_SIZE		4
#define PARTITION_SUBLEVELS	2


// ----------------------------------------------------------------------------
// ScreenPartition - Declaration
// ----------------------------------------------------------------------------

class ScreenPartition
{
public:

	ScreenPartition();
	~ScreenPartition();

	void AddChildren(class hgeRect& InBounds, int Children);
	void DeleteChildren();

private:

	ScreenPartition* ChildPartitions[PARTITION_SIZE];
	hgeRect Bounds;
};

#endif

// EOF
