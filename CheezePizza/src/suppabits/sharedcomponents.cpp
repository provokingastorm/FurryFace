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
	System.SharedData.Int(CMPID_Health) = 0;
	System.SharedData.Int(CMPID_HealthMax) = -1;
}

void LinkComponent::ModifyHealth(int HealthChange)
{
	System.SharedData.Int(CMPID_Health) += HealthChange;
}

void LinkComponent::SetHealthMax(int NewMaxHealth)
{
	System.SharedData.Int(CMPID_HealthMax) = NewMaxHealth;
}

// EOF
