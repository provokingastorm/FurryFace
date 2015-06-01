#ifndef SharedComponents_H_
#define SharedComponents_H_

#ifndef Component_H_
#include "component.h"
#endif


enum ESuppabitsSharedDataID
{
	CMPID_Invalid = 0,
	CMPID_X = 1,
	CMPID_Y = 2,
	CMPID_Health = 3,
};

class HealthComponent : public Component
{
public:
	HealthComponent(class ComponentSystem& System);
	virtual void AddHealth(int HealthAdded) = 0;
};

class LinkComponent : public HealthComponent
{
public:
	LinkComponent(class ComponentSystem& System);
	void AddHealth(int HealthAdded);
};


#endif