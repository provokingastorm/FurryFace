#ifndef OriginsPlayer_H_
#define OriginsPlayer_H_

#ifndef LocalPlayer_H_
#include "localplayer.h"
#endif

class OriginsPlayer : public LocalPlayer
{
public:
	OriginsPlayer();
	~OriginsPlayer();

protected:
	void OnCreatedInternal();
};


#endif