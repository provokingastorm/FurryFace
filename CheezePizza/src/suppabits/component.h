#ifndef Component_H_
#define Component_H_

// ----------------------------------------------------------------------------
// Component - Declaration
// ----------------------------------------------------------------------------

class Component
{
public:
	Component(class ComponentSystem& InSystem)
		: System(InSystem)
	{
	}

	class ComponentSystem& System;

private:
	Component();
};

#endif