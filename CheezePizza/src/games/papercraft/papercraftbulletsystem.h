#ifndef PapercraftBulletSystem_H_
#define PapercraftBulletSystem_H_

#ifndef Vector2D_H_
#include "vector2d.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Defines
// ----------------------------------------------------------------------------

#define MAX_BULLETS		50


// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Enums
// ----------------------------------------------------------------------------

enum EPapercraftBulletColor
{
	PBC_Red		= 0,
};


// ----------------------------------------------------------------------------
// Bullet - Declaration
// ----------------------------------------------------------------------------

struct Bullet
{
	Vector2D Position;
	Vector2D Direction;
	float Angle;
	EPapercraftBulletColor Color;
};


// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Declaration
// ----------------------------------------------------------------------------

class PapercraftBulletSystem
{
public:
	PapercraftBulletSystem();
	~PapercraftBulletSystem();

private:

	Bullet BulletPool[MAX_BULLETS];
};

#endif


// EOF
