#include "cheezepizza.h"
#include "componentsystem.h"
#include "icomponent.h"

// ----------------------------------------------------------------------------
// ComponentSystem - Definition
// ----------------------------------------------------------------------------

ComponentSystem::ComponentSystem(ComponentData& Data)
	: SharedData(Data)
{
}

ComponentSystem::~ComponentSystem()
{
	delete &SharedData;
}