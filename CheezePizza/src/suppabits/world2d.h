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

#ifndef TickLinkedList_H_
#include "ticklinkedlist.h"
#endif

#ifndef Scene2D_H_
#include "scene2d.h"
#endif


class World2D : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(World2D);
	~World2D();

	// --------------------------------------------------------
	//	Tick Methods

	void AddTickObject(class Tickable& InObject);
	void StopTickingObject(Tickable& InObject);

	void AddScene(class Scene2D& Scene, bool bIsCurrentScene);
	void AddPersistentObject(class Scene2DObject& Object, ESceneObjectLayer DrawLayer);

	void AddObjectsToRenderQueue();

	void Start();
	void Tick(float DeltaTime);

	float GetGameTime() const;

	bool IsGamePaused() const;
	void Pause();

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeInternal();
	void ShutdownInternal();

private:
	void ProcessTickRemovals();
	bool AddSceneInternal(class Scene2D& Scene);

	bool HasPersistentObject(class Scene2DObject& Object) const;
	bool HasPersistentObjectInLayer(class Scene2DObject& Object, ESceneObjectLayer DrawLayer) const;

	void AddLayerToRenderQueue(ESceneObjectLayer DrawLayer);

	class Scene2D* CurrentScene;
	std::vector<class Scene2D*> Scenes;
	std::vector<class Scene2DObject*> PersistentObjects[SOL_Max];

	TickLinkedList PreTickList;
	TickLinkedList TickList;
	TickLinkedList PostTickList;
	std::vector<class Tickable*> StopTickQueue;

	float ElapsedGameTime;
	bool bIsGamePaused;
};


// ----------------------------------------------------------------------------
// World2D - Inline Methods
// ----------------------------------------------------------------------------

inline float World2D::GetGameTime() const
{
	return ElapsedGameTime;
}

inline bool World2D::IsGamePaused() const
{
	return bIsGamePaused;
}


#endif