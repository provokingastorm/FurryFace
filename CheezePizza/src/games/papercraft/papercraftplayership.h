#ifndef PapercraftPlayerShip_H_
#define PapercraftPlayerShip_H_

#ifndef Tickable_H_
#include "tickable.h"
#endif

class PapercraftPlayerShip : public Tickable
{
public:
	PapercraftPlayerShip();
	~PapercraftPlayerShip();

	void Tick(float DeltaTime);
	void OnTickStarted();
	void OnTickStopped();

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void ResetVelocity();

	void FirePrimaryWeapon(float DeltaTime);

private:

	class Scene2DObject* SceneObject;
	class PapercraftShipComponentData* SharedData;

	// Components
	class AttackComponent* BasicShotComp;
	class AttackComponent* Crazy88ShotComp;
	class AttackComponent* BombComp;
	class AttackComponent* BeamComp;
	class HealthComponent* HealthComp;
	class TacTriangleComponent* TacComp;

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
