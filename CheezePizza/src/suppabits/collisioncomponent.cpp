#include "cheezepizza.h"
#include "collisioncomponent.h"
#include "collisiondatatypes.h"
#include "screenpartition.h"


CollisionComponent::CollisionComponent()
	: ID(INVALID_COL_INDEX)
	, OwnerProperties(NULL)
{
}

CollisionComponent::~CollisionComponent()
{
	OwnerProperties = NULL;
}

void CollisionComponent::Setup(CollisionOwnerProperties& InProperties)
{
	OwnerProperties = &InProperties;
}

void CollisionComponent::Reset()
{
	OwnerProperties = NULL;
}

// EOF
