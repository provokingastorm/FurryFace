#ifndef PapercraftPlayerDataTypes_H_
#define PapercraftPlayerDataTypes_H_

#ifndef Scene2DDataTypes_H_
#include "scene2ddatatypes.h"
#endif

struct PapercraftPlayerShipData
{
public:

	float X;
	float Y;
	float FacingDirX;
	float FacingDirY;
	float Impulse;

	int ParitionID;
	int PlayerColor;

	// Movement
	float VeriticalMoveScalar;
	float HorizontalMoveScalar;
	Vector2D Velocity;

	// Combat
	float FireCooldownTimer;

	Scene2DObjectData SceneData;
};


#endif