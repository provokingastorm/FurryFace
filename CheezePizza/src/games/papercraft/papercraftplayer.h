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

	void AssociateSceneObject(class Scene2DObject& PlayerObject);
	void DisassociateSceneObject();

protected:

	void OnCreatedInternal();

private:

	class Scene2DObject* SceneObject;
};


#endif

// EOF
