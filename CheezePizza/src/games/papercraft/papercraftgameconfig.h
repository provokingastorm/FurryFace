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
	PapercraftGameConfig();
	PapercraftGameConfig(class ActionHandler& InHandler);
	~PapercraftGameConfig();

	void HandleInput(float DeltaTime);

private:
};

#endif

// EOF
