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
	System.SharedData.Int(CMPID_HealthMax) = 0;
}

int LinkComponent::ModifyHealth(int HealthChange)
{
	const int MaxHealth = System.SharedData.Int(CMPID_HealthMax);
	const int CurrentHealth = System.SharedData.Int(CMPID_Health);
	const int AttemptedHealthChange = CurrentHealth + HealthChange;
	int FinalHealthChange = 0;

	// Don't let the health to extend past max health
	if(MaxHealth > 0 && AttemptedHealthChange > MaxHealth)
	{
		FinalHealthChange = MaxHealth - AttemptedHealthChange;
	}
	// Don't let the health fall below zero
	else if(AttemptedHealthChange < 0)
	{
		FinalHealthChange = -CurrentHealth;
	}
	else
	{
		FinalHealthChange = AttemptedHealthChange;
	}

	System.SharedData.Int(CMPID_Health) += FinalHealthChange;

	return FinalHealthChange;
}

void LinkComponent::SetHealthMax(int NewMaxHealth)
{
	System.SharedData.Int(CMPID_HealthMax) = NewMaxHealth;
}

// EOF
