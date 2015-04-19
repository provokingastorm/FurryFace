#ifndef SharedInputConfigs_H_
#define SharedInputConfigs_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

class DefaultEngineConfig : public InputConfig
{
public:
	DefaultEngineConfig(class GameSession& AssignedSession, class LocalPlayer& AssignedPlayer);
	DefaultEngineConfig(class GameSession& AssignedSession);
	~DefaultEngineConfig();

	void GetKeyUpEvents(std::vector<int>& KeyUpEvents);
	void OnKeyUp(int KeyID);

private:
};


#endif