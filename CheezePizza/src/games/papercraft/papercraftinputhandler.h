#ifndef PapercraftInputHandler_H_
#define PapercraftInputHandler_H_

#ifndef InputHandler_H_
#include "inputhandler.h"
#endif


class PapercraftInputHandler : public InputHandler
{
public:

	PapercraftInputHandler() {}
	~PapercraftInputHandler() {}

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

private:
};

#endif

// EOF
