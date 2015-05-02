#ifndef OriginsGameConfig_H_
#define OriginsGameConfig_H_

#ifndef InputConfig_H_
#include "inputconfig.h"
#endif

class OriginsGameConfig : public InputConfig
{
public:
	OriginsGameConfig();
	OriginsGameConfig(class LocalPlayer& AssignedPlayer);
	~OriginsGameConfig();

	void GetKeyUpEvents(std::vector<int>& KeyUpEvents);
	void OnKeyUp(int KeyID);

	void GetKeyDownEvents(std::vector<int>& KeyUpEvents);
	void OnKeyDown(int KeyID);

	void AssociateSceneObject(class Scene2DObject& PlayerObject);
	void DisassociateSceneObject();

private:

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	class Scene2DObject* SceneObject;

	float MoveDistPerSec;
	float UpVelocity;
	float DownVelocity;
	float RightVelocity;
	float LeftVelocity;

	static const float VelocityPerSec;
	static const float MaxVelocity;
};

#endif