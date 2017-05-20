#ifndef PapercraftPlayerShip_H_
#define PapercraftPlayerShip_H_

#ifndef PapercraftPlayerDataTypes_H_
#include "papercraftplayerdatatypes.h"
#endif

struct PapercraftShipData
{
public:

	PapercraftShipData();

	// Movement
	float VeriticalMoveScalar;
	float HorizontalMoveScalar;
	Vector2D Velocity;

	// Combat
	float FireCooldownTimer;
};

// ----------------------------------------------------------------------------
// PapercraftPlayerShip - Declaration
// ----------------------------------------------------------------------------

class PapercraftPlayerShip
{
public:
	PapercraftPlayerShip();
	~PapercraftPlayerShip();

	// --------------------------------------------------------
	//	Inherited public functions

	void Tick(float DeltaTime);
	void RegisterCollisionComponent();

	// --------------------------------------------------------
	//	Movement public functions

	void MoveHorizontal(float Scalar, float DeltaTime);
	void MoveVertical(float Scalar, float DeltaTime);
	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	Inherited protected functions

	void OnSetPartitionID(int PartitionID);

private:

	PapercraftPlayerShipData ShipData;

	// Components
	class CollisionComponent* CollisionComp;
};

#endif

// EOF
