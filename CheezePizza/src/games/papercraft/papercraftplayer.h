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

	static const float VelocityPerSec;
	static const float MaxVelocity;
};


#endif

// EOF
