#ifndef PapercraftComponents_H_
#define PapercraftComponents_H_

#ifndef Component_H_
#include "component.h"
#endif


// ----------------------------------------------------------------------------
// PapercraftPlayerComponent - Declaration
// ----------------------------------------------------------------------------

// Notes:	This class handles all navigation for the player. Uses the impulse variable from the data component
class PapercraftPlayerComponent : public Component
{
public:
	PapercraftPlayerComponent(class ComponentSystem& System);

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
	TacTriangleComponent(class ComponentSystem& System);

private:
	TacTriangleComponent();
};

// ----------------------------------------------------------------------------
// PlayerHealthComponent - Declaration
// ----------------------------------------------------------------------------

// Note:	This class factors in the health and shield elements of the player (i.e. a damage handler)
//			Uses the shield shared variables from the data component.
class PlayerHealthComponent : public Component
{
public:
	PlayerHealthComponent(class ComponentSystem& System);

private:
	PlayerHealthComponent();
};

// ----------------------------------------------------------------------------
// PlayerAttackComponent - Declaration
// ----------------------------------------------------------------------------

// Notes:	This class handles all weapons for the player. Uses missle capacity, turrets etc from the data component
class PlayerAttackComponent : public Component
{
public:
	PlayerAttackComponent(class ComponentSystem& System);

private:
	PlayerAttackComponent();
};


#endif

// EOF
