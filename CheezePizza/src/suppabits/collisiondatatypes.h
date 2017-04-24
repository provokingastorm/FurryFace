#ifndef CollisionDataTypes_H_
#define CollisionDataTypes_H_

#ifndef HGERECT_H
#include "hgerect.h"
#endif

struct CollisionComponentData
{
public:

	int PartitonID;
	bool bIsActive;
	DWORD ChannelFlags;
	hgeRect Bounds;
	CollisionCallback* Callback;
	DWORD ResponseFlags;
};

#endif