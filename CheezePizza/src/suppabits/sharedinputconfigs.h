#ifndef SharedInputConfigs_H_
#define SharedInputConfigs_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

class DefaultEngineConfig : public InputConfig
{
public:
	DefaultEngineConfig();
	DefaultEngineConfig(class LocalPlayer& AssignedPlayer);
	~DefaultEngineConfig();

private:
};


#endif