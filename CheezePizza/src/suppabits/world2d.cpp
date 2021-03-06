#include "cheezepizza.h"
#include "world2d.h"
#include "collisionsubsystem.h"
#include "screenpartition.h"
#include "scene2d.h"
#include "scene2dobject.h"
#include "cheezepizzaengine.h"


// ----------------------------------------------------------------------------
// World2D - Definition
// ----------------------------------------------------------------------------

void World2D::InitializeInternal()
{
	CurrentScene = NULL;
	ElapsedGameTime = 0.0f;
	bIsGamePaused = false;

	Partition = new ScreenPartition();

	StopTickQueue.clear();

	PreTickList.SetTickType(ETT_PreTick);
	TickList.SetTickType(ETT_Tick);
	PostTickList.SetTickType(ETT_PostTick);
}

void World2D::ShutdownInternal()
{
	delete Partition;

	// Don't need to delete CurrentScene because it should be contained in the Scenes vector.
	CurrentScene = NULL;

	ActiveObjects->~vector();

	SAFE_DELETE_STL_VECTOR(Scenes);

	for(int j = 0; j < SOL_Max; ++j)
	{
		const int NumObjs = PersistentObjects[j].size();

		for(int h = 0; h < NumObjs; ++h)
		{
			delete PersistentObjects[j][h];
		}

		PersistentObjects[j].~vector();
	}

	StopTickQueue.~vector();
}

void World2D::FirstEngineTickInternal()
{
	if(CurrentScene != NULL)
	{
		CurrentScene->EnterScene();
	}

	for(int i = 0; i < SOL_Max; i++)
	{
		const int NumObjs = PersistentObjects[i].size();

		for(int j = 0; j < NumObjs; j++)
		{
			Scene2DObject& Object = *PersistentObjects[i][j];
			OnSceneObjectEntered(Object);
		}
	}
}

void World2D::Tick(float DeltaTime)
{
	if(!IsGamePaused())
	{
		ElapsedGameTime += DeltaTime;

		PreTickList.Tick(DeltaTime);

		RecalculateObjectsPartition();

		CollisionSubsystem::Instance().CheckForCollisions(DeltaTime);

		TickList.Tick(DeltaTime);
		PostTickList.Tick(DeltaTime);
	}

	// Objects are removed from the tick lists only after all the ticking is finished
	ProcessTickRemovals();

	// Populate the render queue
	AddObjectsToRenderQueue();
}

void World2D::Pause()
{
	if(!bIsGamePaused)
	{
		bIsGamePaused = true;
	}
}

void World2D::AddTickObject(Tickable& InObject)
{
	switch(InObject.GetTickType())
	{
	case ETT_Tick:
		TickList.Append(InObject);
		break;

	case ETT_PreTick:
		PreTickList.Append(InObject);
		break;

	case ETT_PostTick:
		PostTickList.Append(InObject);
		break;

	default:
		CPForceAssert("Unhandled tick type");
		break;
	}
}

void World2D::StopTickingObject(Tickable& InObject)
{
	// Defer removing the object from the tick list until all ticking is finished. 
	StopTickQueue.push_back(&InObject);
}

void World2D::RecalculateObjectsPartition()
{
	for(int DrawLayer = 0; DrawLayer < SOL_Max; DrawLayer++)
	{
		const int NumObjs = PersistentObjects[DrawLayer].size();

		for(int i = 0; i < NumObjs; ++i)
		{
			Scene2DObject& Obj = *(PersistentObjects[DrawLayer][i]);

			// Only update the object's partition ID if they moved to avoid unnecessary calculations
			if(Obj.MovedThisTick())
			{
				Vector2D Position = Obj.GetPosition();
				int PartitionID = Partition->GetPartitionIDForPoint(Position.X, Position.Y);

				// NOTE: We allow setting invalid partition IDs (-1) which means the object is off-screen.
				Obj.SetPartition(PartitionID);
			}
		}
	}
}

void World2D::ProcessTickRemovals()
{
	const int NumTickRemovals = StopTickQueue.size();

	for(int i = 0; i < NumTickRemovals; ++i)
	{
		Tickable& ToRemove = *StopTickQueue[i];
		switch(ToRemove.GetTickType())
		{
		case ETT_Tick:
			TickList.Remove(ToRemove);
			break;

		case ETT_PreTick:
			PreTickList.Remove(ToRemove);
			break;

		case ETT_PostTick:
			PostTickList.Remove(ToRemove);
			break;

		default:
			CPForceAssert("Unhandled tick type");
			break;
		}
	}

	StopTickQueue.clear();
}

void World2D::AddScene(class Scene2D& Scene, bool bIsCurrentScene)
{
	const bool bWasAdded = AddSceneInternal(Scene);

	if(bWasAdded && bIsCurrentScene)
	{
		CurrentScene = &Scene;
	}
}

bool World2D::AddSceneInternal(Scene2D& Scene)
{
	bool bAlreadyTracked = false;
	const int NumScenes = Scenes.size();

#if defined(_DEBUG)
	if(NumScenes <= 0)
	{
		// If CurrentScene is not NULL, the pointer was never NULL'd on init, cleared 
		// or somebody forgot to clear the pointer after removing the scene2d.
		CPAssert(CurrentScene == NULL, "The Scene2DManager has a CurrentScene without having any Scene2D!");
	}
#endif

	for(int i = 0; i < NumScenes; ++i)
	{
		if(Scenes[i] == &Scene)
		{
			bAlreadyTracked = true;
			break;
		}
	}

	if(!bAlreadyTracked)
	{
		Scenes.push_back(&Scene);
		return true;
	}

	return false;
}

void World2D::AddPersistentObject(Scene2DObject& Object, ESceneObjectLayer DrawLayer)
{
	if(!HasPersistentObject(Object))
	{
		PersistentObjects[DrawLayer].push_back(&Object);

		if(HasTicked())
		{
			OnSceneObjectEntered(Object);
		}
	}
}

bool World2D::HasPersistentObject(Scene2DObject& Object) const
{
	return (	
				HasPersistentObjectInLayer(Object, SOL_Background)
			||	HasPersistentObjectInLayer(Object, SOL_Layer1)
			||	HasPersistentObjectInLayer(Object, SOL_Layer2)
			||	HasPersistentObjectInLayer(Object, SOL_Foreground)
			);
}

bool World2D::HasPersistentObjectInLayer(Scene2DObject& Object, ESceneObjectLayer DrawLayer) const
{
	CPAssert(DrawLayer != SOL_Max, "Scene2DManager::HasPersistentObjectInLayer() -  Using an invalid DrawLayer");

	const int NumObjs = PersistentObjects[DrawLayer].size();
	for(int i = 0; i < NumObjs; ++i)
	{
		if(PersistentObjects[DrawLayer][i] == &Object)
		{
			return true;
		}
	}

	return false;
}

void World2D::OnSceneObjectEntered(class Scene2DObject& Object)
{
	AddTickObject(Object);

	Object.RegisterCollisionComponent();

	Vector2D Position = Object.GetPosition();
	int PartitionID = Partition->GetPartitionIDForPoint(Position.X, Position.Y);
	Object.SetPartition(PartitionID);

	Object.Start();
}

void World2D::AddObjectsToRenderQueue()
{
	AddLayerToRenderQueue(SOL_Background);
	AddLayerToRenderQueue(SOL_Layer1);
	AddLayerToRenderQueue(SOL_Layer2);
	AddLayerToRenderQueue(SOL_Foreground);
}

void World2D::AddLayerToRenderQueue(ESceneObjectLayer DrawLayer)
{
	CPAssert(DrawLayer != SOL_Max, "Scene2DManager::AddLayerToRenderQueue() -  Using an invalid DrawLayer");

	// First, add objects associated to the given layer from the current visible scene
	if(CurrentScene != NULL)
	{
		CurrentScene->AddLayerToRenderQueue(DrawLayer);
	}

	// Now, add all persistent objects associated to the given layer
	const int NumObjs = PersistentObjects[DrawLayer].size();
	for(int i = 0; i < NumObjs; ++i)
	{
		Scene2DObject& SceneObject = (*PersistentObjects[DrawLayer][i]);
		IRenderable* RenderObject = SceneObject.GetRenderObject();

		if(RenderObject != NULL)
		{
			CheezePizzaEngine::Instance().AddToRenderQueue(*RenderObject);
		}
	}
}

void World2D::SetScreenBounds(const hgeRect& InScreenBounds)
{
	ScreenBounds = InScreenBounds;
	
	// TODO: Make the rows, columns configurable (maybe in an INI file)
	Partition->RecalculateBounds(ScreenBounds, 3, 2);
}

const ScreenPartition& World2D::GetPartition() const
{
	return *Partition;
}

// EOF
