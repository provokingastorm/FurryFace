#ifndef SharedInputConfigs_H_
#define SharedInputConfigs_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

// ----------------------------------------------------------------------------
// DefaultEngineConfig - Declaration
// ----------------------------------------------------------------------------

class DefaultEngineConfig : public InputConfig
{
public:
	DefaultEngineConfig();
	DefaultEngineConfig(class ActionHandler& InHandler);
	~DefaultEngineConfig();

private:
};


#endif

// EOF
