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

	// --------------------------------------------------------
	//	Inherited public functions

	void PreTick(float DeltaTime);
	void Tick(float DeltaTime);
	void RegisterCollisionComponent();

	// --------------------------------------------------------
	//	Movement public functions

	void MoveHorizontal(float Scalar);
	void MoveVertical(float Scalar);
	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	Inherited protected functions

	void OnSetPartitionID(int PartitionID);
	void HandleAction(int ActionType);

private:

	// Components
	class AttackComponent* BasicShotComp;
	class AttackComponent* Crazy88ShotComp;
	class AttackComponent* BombComp;
	class AttackComponent* BeamComp;
	class TacTriangleComponent* TacComp;
	class CollisionComponent* CollisionComp;

	// Movement
	float VeriticalMoveScalar;
	float HorizontalMoveScalar;
	Vector2D Velocity;

	// Combat
	float FireCooldownTimer;

	static const float VelocityPerSec;
	static const float MaxVelocity;
};

#endif

// EOF
