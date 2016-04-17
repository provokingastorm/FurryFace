#ifndef InputCoordinator_H_
#define InputCoordinator_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif

// ----------------------------------------------------------------------------
// InputCoordinator - Declaration
// ----------------------------------------------------------------------------

class InputCoordinator : public Tickable
{
public:

	InputCoordinator();

private:

	void PreTick(float DeltaTime);
};


#endif

// EOF
