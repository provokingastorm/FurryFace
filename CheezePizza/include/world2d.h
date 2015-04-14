#ifndef World2D_H_
#define World2D_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef Vector_STL_H_
#include <vector>
#endif

#ifndef Map_STL_H_
#include <map>
#endif

#ifndef Scene2D_H_
#include "scene2d.h"
#endif


class World2D : public EngineSubsystem
{
public:
	World2D();
	~World2D();

	void AddScene(class Scene2D& Scene, bool bIsCurrentScene);
	void AddPersistentObject(class Scene2DObject& Object, ESceneObjectLayer DrawLayer);

	void AddObjectsToRenderQueue(class CheezePizzaEngine& Engine);

	void Start();

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void ShutdownInternal();

private:
	bool AddSceneInternal(class Scene2D& Scene);

	bool HasPersistentObject(class Scene2DObject& Object) const;
	bool HasPersistentObjectInLayer(class Scene2DObject& Object, ESceneObjectLayer DrawLayer) const;

	void AddLayerToRenderQueue(class CheezePizzaEngine& Engine, ESceneObjectLayer DrawLayer);

	class Scene2D* CurrentScene;
	std::vector<class Scene2D*> Scenes;
	std::vector<class Scene2DObject*> PersistentObjects[SOL_Max];
};


#endif