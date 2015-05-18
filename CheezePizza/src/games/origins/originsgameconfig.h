#ifndef OriginsGameConfig_H_
#define OriginsGameConfig_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

// ----------------------------------------------------------------------------
// OriginsGameConfig - Declaration
// ----------------------------------------------------------------------------

class OriginsGameConfig : public InputConfig
{
public:
	OriginsGameConfig();
	OriginsGameConfig(class LocalPlayer& AssignedPlayer);
	~OriginsGameConfig();

	void HandleInput(float DeltaTime);

private:
};

#endif