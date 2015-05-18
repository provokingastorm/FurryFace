#ifndef ComponentSystem_H_
#define ComponentSystem_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

// ----------------------------------------------------------------------------
// ComponentSystem - Declaration
// ----------------------------------------------------------------------------

class ComponentSystem
{
public:

	ComponentSystem(ComponentData& Data);
	~ComponentSystem();

	ComponentData& SharedData;

private:

	ComponentSystem();
};

#endif