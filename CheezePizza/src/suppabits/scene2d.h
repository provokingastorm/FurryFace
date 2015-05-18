#ifndef Scene2D_H_
#define Scene2D_H_

#ifndef _VECTOR_
#include <vector>
#endif

// ----------------------------------------------------------------------------
// Scene2D - Enums
// ----------------------------------------------------------------------------

enum ESceneObjectLayer
{
	SOL_Background	= 0,
	SOL_Layer1		= 1,
	SOL_Layer2		= 2,
	SOL_Foreground	= 3,
	SOL_Max			= 4,
};

// ----------------------------------------------------------------------------
// Scene2D - Declaration
// ----------------------------------------------------------------------------

class Scene2D
{
public:
	Scene2D();
	~Scene2D();

	void Add(class Scene2DObject& Object, ESceneObjectLayer DrawLayer);
	void AddLayerToRenderQueue(ESceneObjectLayer DrawLayer);

	void EnterScene();
	void ExitScene();

private:
	bool HasSceneObject(class Scene2DObject& Object);
	bool HasSceneObject(class Scene2DObject& Object, ESceneObjectLayer DrawLayer);

	std::vector<class Scene2DObject*> SceneObjects[SOL_Max];
};

#endif	// #ifndef Scene2D_H_