#ifndef PapercraftComponents_H_
#define PapercraftComponents_H_

#ifndef SharedComponents_H_
#include "sharedcomponents.h"
#endif


// ----------------------------------------------------------------------------
// PapercraftPlayerComponent - Declaration
// ----------------------------------------------------------------------------

// Notes:	This class handles all navigation for the player. Uses the impulse variable from the data component
class PapercraftPlayerComponent : public Component
{
public:
	PapercraftPlayerComponent(class ComponentData& InData);

private:
	PapercraftPlayerComponent();
};

// ----------------------------------------------------------------------------
// TacTriangleComponent - Declaration
// ----------------------------------------------------------------------------

// Notes:	This class handles all the tac triangle calculation and saves out the attributes to its data component
class TacTriangleComponent : public Component
{
public:
	TacTriangleComponent(class ComponentData& InData);

private:
	TacTriangleComponent();
};

// ----------------------------------------------------------------------------
// PlayerHealthComponent - Declaration
// ----------------------------------------------------------------------------

// Note:	This class factors in the health and shield elements of the player (i.e. a damage handler)
//			Uses the shield shared variables from the data component.
class PlayerHealthComponent : public HealthComponent
{
public:
	PlayerHealthComponent(class ComponentData& InData);

private:
	PlayerHealthComponent();
};

// ----------------------------------------------------------------------------
// AttackComponent - Declaration
// ----------------------------------------------------------------------------

class AttackComponent : public Component
{
public:
	AttackComponent(class ComponentData& InData)
		: Component(InData)
	{
	}

	virtual void Fire(float DeltaTime) = 0;

private:
	AttackComponent();
};

// ----------------------------------------------------------------------------
// PlayerBasicAttackComponent - Declaration
// ----------------------------------------------------------------------------

class BasicAttackComponent : public AttackComponent
{
public:
	BasicAttackComponent(class ComponentData& InData);

	void Fire(float DeltaTime);

private:
	BasicAttackComponent();
};

// ----------------------------------------------------------------------------
// Crazy88AttackComponent - Declaration
// ----------------------------------------------------------------------------

class Crazy88AttackComponent : public AttackComponent
{
public:
	Crazy88AttackComponent(class ComponentData& InData);

	void Fire(float DeltaTime);

private:
	Crazy88AttackComponent();
};

// ----------------------------------------------------------------------------
// BombAttackComponent - Declaration
// ----------------------------------------------------------------------------

class BombAttackComponent : public AttackComponent
{
public:
	BombAttackComponent(class ComponentData& InData);

	void Fire(float DeltaTime);

private:
	BombAttackComponent();
};

// ----------------------------------------------------------------------------
// Crazy88AttackComponent - Declaration
// ----------------------------------------------------------------------------

class BeamAttackComponent : public AttackComponent
{
public:
	BeamAttackComponent(class ComponentData& InData);

	void Fire(float DeltaTime);

private:
	BeamAttackComponent();
};


#endif

// EOF
