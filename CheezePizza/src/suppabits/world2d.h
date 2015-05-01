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

	// --------------------------------------------------------
	//	EngineSubsystem inherited public methods

	void Tick(float DeltaTime);

	// --------------------------------------------------------
	//	Tick Methods

	void AddTickObject(class Tickable& InObject);
	void StopTickingObject(Tickable& InObject);

	void AddScene(class Scene2D& Scene, bool bIsCurrentScene);
	void AddPersistentObject(class Scene2DObject& Object, ESceneObjectLayer DrawLayer);

	void AddObjectsToRenderQueue();

	double GetGameTime() const;

	bool IsGamePaused() const;
	void Pause();

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();
	void FirstEngineTickInternal();

private:

	// --------------------------------------------------------
	//	Tick Methods

	void ProcessTickRemovals();

	// --------------------------------------------------------
	//	Scene2D Methods

	bool AddSceneInternal(class Scene2D& Scene);

	bool HasPersistentObject(class Scene2DObject& Object) const;
	bool HasPersistentObjectInLayer(class Scene2DObject& Object, ESceneObjectLayer DrawLayer) const;

	void OnSceneObjectEntered(class Scene2DObject& Object);

	void AddLayerToRenderQueue(ESceneObjectLayer DrawLayer);

	// --------------------------------------------------------
	//	Scene2D variables

	class Scene2D* CurrentScene;
	std::vector<class Scene2D*> Scenes;
	std::vector<class Scene2DObject*> PersistentObjects[SOL_Max];

	// --------------------------------------------------------
	//	Tick variables

	TickLinkedList PreTickList;
	TickLinkedList TickList;
	TickLinkedList PostTickList;
	std::vector<class Tickable*> StopTickQueue;

	double ElapsedGameTime;
	bool bIsGamePaused;
};


// ----------------------------------------------------------------------------
// World2D - Inline Methods
// ----------------------------------------------------------------------------

inline double World2D::GetGameTime() const
{
	return ElapsedGameTime;
}

inline bool World2D::IsGamePaused() const
{
	return bIsGamePaused;
}


#endif