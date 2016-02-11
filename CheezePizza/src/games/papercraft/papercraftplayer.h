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

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

protected:

	void OnCreatedInternal();

private:

	class PapercraftPlayerShip* Ship;
};


#endif

// EOF
