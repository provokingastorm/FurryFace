#ifndef Scene2DDataTypes_H_
#define Scene2DDataTypes_H_

struct Scene2DObjectData
{
public:
	Scene2DObjectData()
		: RenderObject(NULL)
	{
	}

	class IRenderable* RenderObject;
};

#endif