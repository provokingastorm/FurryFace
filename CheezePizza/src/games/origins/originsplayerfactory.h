#ifndef OriginsPlayerFactory_H_
#define OriginsPlayerFactory_H_

#ifndef PlayerFactory_H_
#include "playerfactory.h"
#endif

class OriginsPlayerFactory : public PlayerFactory
{
public:
	OriginsPlayerFactory(class GameSession& AssignedSession);

protected:
	class LocalPlayer* CreatePlayer();
	class Hud* CreateHud();
};

#endif