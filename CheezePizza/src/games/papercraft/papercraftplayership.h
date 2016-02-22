#ifndef PapercraftPlayerShip_H_
#define PapercraftPlayerShip_H_

#ifndef Scene2DObject_H_
#include "scene2dobject.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftPlayerShip - Declaration
// ----------------------------------------------------------------------------

class PapercraftPlayerShip : public Scene2DObject
{
public:
	PapercraftPlayerShip();
	~PapercraftPlayerShip();

	void Tick(float DeltaTime);

	void RegisterCollisionComponent();

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

private:

	// Components
	class AttackComponent* BasicShotComp;
	class AttackComponent* Crazy88ShotComp;
	class AttackComponent* BombComp;
	class AttackComponent* BeamComp;
	class TacTriangleComponent* TacComp;

	class CollisionComponent* CollisionComp;

	float UpVelocity;
	float DownVelocity;
	float RightVelocity;
	float LeftVelocity;

	float FireCooldownTimer;

	static const float VelocityPerSec;
	static const float MaxVelocity;
};

#endif

// EOF
