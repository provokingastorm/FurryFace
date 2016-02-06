#include "cheezepizza.h"
#include "papercraftcomponents.h"

// ----------------------------------------------------------------------------
// PapercraftShipComponentData - Definition
// ----------------------------------------------------------------------------

PapercraftPlayerComponent::PapercraftPlayerComponent(ComponentData& InData)
	: Component(InData)
{
}

// ----------------------------------------------------------------------------
// TacTriangleComponent - Definition
// ----------------------------------------------------------------------------

TacTriangleComponent::TacTriangleComponent(ComponentData& InData)
	: Component(InData)
{
}

// ----------------------------------------------------------------------------
// PlayerHealthComponent - Definition
// ----------------------------------------------------------------------------

PlayerHealthComponent::PlayerHealthComponent(ComponentData& InData)
	: HealthComponent(InData)
{
}

// ----------------------------------------------------------------------------
// BasicAttackComponent - Definition
// ----------------------------------------------------------------------------

BasicAttackComponent::BasicAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void BasicAttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// Crazy88AttackComponent - Definition
// ----------------------------------------------------------------------------

Crazy88AttackComponent::Crazy88AttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void Crazy88AttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// BombAttackComponent - Definition
// ----------------------------------------------------------------------------

BombAttackComponent::BombAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void BombAttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// BeamAttackComponent - Definition
// ----------------------------------------------------------------------------

BeamAttackComponent::BeamAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void BeamAttackComponent::Fire(float DeltaTime)
{

}

// EOF
