#include "cheezepizza.h"
#include "papercraftcomponents.h"
#include "papercraftcomponentdata.h"
#include "papercraftbulletsystem.h"
#include "papercraftstructures.h"

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

void BasicAttackComponent::Tick(float DeltaTime)
{
}

void BasicAttackComponent::Fire(float DeltaTime)
{
	Bullet NewBullet;
	NewBullet.Position.X = SharedData.Float(CMPID_X);
	NewBullet.Position.Y = SharedData.Float(CMPID_Y);
	NewBullet.Direction.X = SharedData.Float(CMPID_FacingDirX);
	NewBullet.Direction.Y = SharedData.Float(CMPID_FacingDirY);
	NewBullet.Behavior = BBT_Default;
	NewBullet.Color = GetPlayerColorFromInt(SharedData.Int(PDID_PlayerColor));

	PapercraftBulletSystem::Instance().SpawnBullet(NewBullet);
}

// ----------------------------------------------------------------------------
// Crazy88AttackComponent - Definition
// ----------------------------------------------------------------------------

Crazy88AttackComponent::Crazy88AttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void Crazy88AttackComponent::Tick(float DeltaTime)
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

void BombAttackComponent::Tick(float DeltaTime)
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

void BeamAttackComponent::Tick(float DeltaTime)
{
}

void BeamAttackComponent::Fire(float DeltaTime)
{
}

// EOF
