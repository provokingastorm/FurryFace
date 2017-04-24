#ifndef PapercraftPlayer_H_
#define PapercraftPlayer_H_

#ifndef LocalPlayer_H_
#include "localplayer.h"
#endif

#ifndef Scene2DDataTypes_H_
#include "scene2ddatatypes.h"
#endif

class PapercraftPlayer : public LocalPlayer
{
public:
	PapercraftPlayer();
	~PapercraftPlayer();

protected:

	void OnCreatedInternal();

private:

	class PapercraftPlayerShip* Ship;
};


#endif

// EOF
