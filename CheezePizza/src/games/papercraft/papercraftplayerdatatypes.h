#ifndef PapercraftPlayerDataTypes_H_
#define PapercraftPlayerDataTypes_H_

#ifndef Scene2DDataTypes_H_
#include "scene2ddatatypes.h"
#endif

#ifndef CollisionComponent_H_
#include "collisioncomponent.h"
#endif

struct PapercraftPlayerShipData
{
public:

	float X;
	float Y;
	float FacingDirX;
	float FacingDirY;
	float Impulse;

	int PlayerColor;

	// Movement
	float VeriticalMoveScalar;
	float HorizontalMoveScalar;
	Vector2D Velocity;

	// Combat
	float FireCooldownTimer;

	// Collision
	CollisionOwnerProperties CollisionProperties;

	Scene2DObjectData SceneData;
};


#endif