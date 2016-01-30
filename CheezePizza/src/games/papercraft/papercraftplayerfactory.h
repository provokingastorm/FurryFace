#ifndef PapercraftPlayerFactory_H_
#define PapercraftPlayerFactory_H_

#ifndef PlayerFactory_H_
#include "playerfactory.h"
#endif

class PapercraftPlayerFactory : public PlayerFactory
{
public:
	PapercraftPlayerFactory();

protected:
	class LocalPlayer* CreatePlayer();
	class Hud* CreateHud();
};

#endif

// EOF
