#ifndef Component_H_
#define Component_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

// ----------------------------------------------------------------------------
// Component - Declaration
// ----------------------------------------------------------------------------

class Component
{
public:
	Component(ComponentData& InData)
		: SharedData(InData)
	{
	}

	ComponentData& SharedData;

private:
	Component();
};

#endif

// EOF
