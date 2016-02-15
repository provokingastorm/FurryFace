#ifndef PapercraftBulletBehaviors_H_
#define PapercraftBulletBehaviors_H_

#ifndef Vector2D_H_
#include "vector2d.h"
#endif


// ----------------------------------------------------------------------------
// PapercraftBulletBehavior - Enums
// ----------------------------------------------------------------------------

enum EPapercraftBulletColor
{
	PBC_White	= 0,
	PBC_Red		= 1,
};

enum EBulletBehaviorType
{
	BBT_Default		= 0,
	BBT_Max
};


// ----------------------------------------------------------------------------
// Bullet - Declaration
// ----------------------------------------------------------------------------

struct Bullet
{
	Vector2D Position;
	Vector2D Direction;
	EBulletBehaviorType Behavior;
	float Angle;

	Bullet()
		: Position(Vector2D(0.0f, 0.0f))
		, Direction(Vector2D(0.0f, 0.0f))
		, Behavior(BBT_Default)
		, Angle(0.0f)
	{
	}

	void ResetToDefaults()
	{
		Position.X = 0.0f;
		Position.Y = 0.0f;

		Direction.X = 0.0f;
		Direction.Y = 0.0f;

		Behavior = BBT_Default;
		Angle = 0.0f;
	}
};

// ----------------------------------------------------------------------------
// PapercraftBulletBehavior - Declaration
// ----------------------------------------------------------------------------

class PapercraftBulletBehavior
{ 
public:

	PapercraftBulletBehavior();

	virtual void TickBullet(float DeltaTime, Bullet& ToTick) {}

	EPapercraftBulletColor Color;
};

// ----------------------------------------------------------------------------
// PapercraftBulletBehaviorDefault - Declaration
// ----------------------------------------------------------------------------

class PapercraftBulletBehaviorDefault : public PapercraftBulletBehavior
{ 
public:

	PapercraftBulletBehaviorDefault();

	void TickBullet(float DeltaTime, Bullet& ToTick);

private:

	class BasicShotRenderable* BulletRO;
	class Scene2DObject* BulletScene;
	class hgeAnimation* BulletAnim;
};

#endif

// EOF
