#ifndef PapercraftGameConfig_H_
#define PapercraftGameConfig_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftGameConfig - Declaration
// ----------------------------------------------------------------------------

class PapercraftGameConfig : public InputConfig
{
public:

	PapercraftGameConfig(class PapercraftPlayerShip& InShip);
	~PapercraftGameConfig();

	void HandleInput(float DeltaTime);

private:

	// Hide default constructor in favor of using a parameterized constructor to initialize reference objects
	PapercraftGameConfig();

	class PapercraftPlayerShip& PlayerShip;
};

#endif

// EOF
