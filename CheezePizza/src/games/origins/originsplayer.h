#ifndef OriginsPlayer_H_
#define OriginsPlayer_H_

#ifndef LocalPlayer_H_
#include "localplayer.h"
#endif

class OriginsPlayer : public LocalPlayer
{
public:
	OriginsPlayer();
	~OriginsPlayer();

	void AssociateSceneObject(class Scene2DObject& PlayerObject);
	void DisassociateSceneObject();

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void ResetVelocity();

protected:

	void OnCreatedInternal();

private:

	class Scene2DObject* SceneObject;

	float UpVelocity;
	float DownVelocity;
	float RightVelocity;
	float LeftVelocity;

	static const float VelocityPerSec;
	static const float MaxVelocity;
};


#endif

// EOF
