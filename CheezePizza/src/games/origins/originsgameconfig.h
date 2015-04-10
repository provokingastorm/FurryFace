#ifndef OriginsGameConfig_H_
#define OriginsGameConfig_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

class OriginsGameConfig : public InputConfig
{
public:
	OriginsGameConfig(class GameSession& AssignedSession, class LocalPlayer& AssignedPlayer);
	OriginsGameConfig(class GameSession& AssignedSession);
	~OriginsGameConfig();

	void GetKeyUpEvents(std::vector<int>& KeyUpEvents);
	void OnKeyUp(int KeyID);
};

#endif