#ifndef InputHandler_H_
#define InputHandler_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif

// ----------------------------------------------------------------------------
// InputHandler - Declaration
// ----------------------------------------------------------------------------

class InputHandler : public Tickable
{
public:

	InputHandler();

private:

	void PreTick(float DeltaTime);
};


#endif

// EOF
