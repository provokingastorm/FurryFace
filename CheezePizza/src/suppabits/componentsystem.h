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

	float& operator[] (const int DataID);
	const float& operator[] (const int DataID) const;

private:

	ComponentData& SharedData;

	ComponentSystem();
};


// ----------------------------------------------------------------------------
// ComponentSystem - Inline Function
// ----------------------------------------------------------------------------

inline float& ComponentSystem::operator[] (const int DataID)
{
	return SharedData[DataID];
}

inline const float& ComponentSystem::operator[] (const int DataID) const
{
	return SharedData[DataID];
}

#endif