#ifndef SharedComponents_H_
#define SharedComponents_H_

#ifndef Component_H_
#include "component.h"
#endif

// ----------------------------------------------------------------------------
// SharedComponents - Enums
// ----------------------------------------------------------------------------

enum ESuppabitsSharedDataID
{
	CMPID_Invalid		= 0,
	CMPID_X				= 1,
	CMPID_Y				= 2,
	CMPID_Health		= 3,
	CMPID_HealthMax		= 4,
	CMPID_FacingDirX	= 5,
	CMPID_FacingDirY	= 6,
	CMPID_PartitionID	= 7,
	CMPID_Max,
};

// ----------------------------------------------------------------------------
// HealthComponent - Declaration
// ----------------------------------------------------------------------------

class HealthComponent : public Component
{
public:
	HealthComponent(class ComponentData& InData);

	virtual int ModifyHealth(int HealthChange) = 0;
	virtual void SetHealthMax(int NewMaxHealth) = 0;
};


#endif

// EOF
