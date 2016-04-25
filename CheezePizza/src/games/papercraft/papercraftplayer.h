#ifndef PapercraftPlayer_H_
#define PapercraftPlayer_H_

#ifndef LocalPlayer_H_
#include "localplayer.h"
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
