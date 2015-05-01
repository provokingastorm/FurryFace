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

	void AssociateSceneObject(class Scene2DObject& PlayerObject);
	void DisassociateSceneObject();

private:

	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	class Scene2DObject* SceneObject;
};

#endif