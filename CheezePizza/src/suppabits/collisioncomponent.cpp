#include "cheezepizza.h"
#include "collisioncomponent.h"
#include "screenpartition.h"


CollisionComponent::CollisionComponent()
	: ID(INVALID_COL_INDEX)
	, PartitonID(INVALID_PARTITION_ID)
	, bIsActive(false)
	, ChannelFlags(COLLISIONCHANNEL_None)
	, Bounds(hgeRect(0.0f, 0.0f, 0.0f, 0.0f))
	, Callback(NULL)
	, ResponseFlags(COLLISION_None)
{
}

CollisionComponent::~CollisionComponent()
{
	if(Callback != NULL)
	{
		delete Callback;
		Callback = NULL;
	}
}

// EOF
