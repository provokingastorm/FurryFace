#include "cheezepizza.h"
#include "sharedcomponents.h"
#include "componentsystem.h"

HealthComponent::HealthComponent(ComponentSystem& System)
	: Component(System)
{
}

LinkComponent::LinkComponent(ComponentSystem& System)
	: HealthComponent(System)
{
}

void LinkComponent::AddHealth(int HealthAdded)
{
	System.SharedData.Int(CMPID_Health) += HealthAdded;
}