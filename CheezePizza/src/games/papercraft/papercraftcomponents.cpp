#include "cheezepizza.h"
#include "papercraftcomponents.h"

#include "world2d.h"
#include "sharedrenderables.h"
#include "scene2dobject.h"

#include "cheezepizzaengine.h"
#include "hgeresource.h"

// ----------------------------------------------------------------------------
// PapercraftShipComponentData - Definition
// ----------------------------------------------------------------------------

PapercraftPlayerComponent::PapercraftPlayerComponent(ComponentData& InData)
	: Component(InData)
{
}

// ----------------------------------------------------------------------------
// TacTriangleComponent - Definition
// ----------------------------------------------------------------------------

TacTriangleComponent::TacTriangleComponent(ComponentData& InData)
	: Component(InData)
{
}

// ----------------------------------------------------------------------------
// PlayerHealthComponent - Definition
// ----------------------------------------------------------------------------

PlayerHealthComponent::PlayerHealthComponent(ComponentData& InData)
	: HealthComponent(InData)
{
}

// ----------------------------------------------------------------------------
// BasicAttackComponent - Definition
// ----------------------------------------------------------------------------

class BasicShotRenderable : public IRenderable
{
public:
	BasicShotRenderable();
	~BasicShotRenderable();

	void AddAnimation(class hgeAnimation& InAnim);

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void SetHotSpot(float X, float Y);
	void OnStart();
	void OnStop();
	void OnPause();

private:
	class hgeAnimation* CurrentAnim;
	Vector2D HotSpot;
};

BasicShotRenderable::BasicShotRenderable()
	: CurrentAnim(NULL)
	, HotSpot(0.0f, 0.0f)
{
}

BasicShotRenderable::~BasicShotRenderable()
{
	CurrentAnim = NULL;
}

void BasicShotRenderable::AddAnimation(hgeAnimation& InAnim)
{
	CurrentAnim = &InAnim;
}

void BasicShotRenderable::Tick(float DeltaTime)
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Update(DeltaTime);
	}
}

void BasicShotRenderable::Render(class HGE& Engine)
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Render(HotSpot.X, HotSpot.Y);
	}
}

void BasicShotRenderable::SetHotSpot(float X, float Y)
{
	HotSpot.X = X + 20.0f;
	HotSpot.Y = Y + 20.0f;
}

void BasicShotRenderable::OnStart()
{
	if(CurrentAnim != NULL)
	{
		CurrentAnim->Play();
	}
}

void BasicShotRenderable::OnStop()
{
}

void BasicShotRenderable::OnPause()
{
}

// ----------------------------------------------------------------------------
// BasicAttackComponent - Definition
// ----------------------------------------------------------------------------

BasicAttackComponent::BasicAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
	BulletAnim = CE.ResourceManager->GetAnimation("animBullet");
	if(BulletAnim != NULL)
	{
		BasicShotRenderable* BulletRO = new BasicShotRenderable();
		BulletRO->AddAnimation(*BulletAnim);

		Scene2DObject& SceneObjRef = *(new Scene2DObject());
		SceneObjRef.SetRenderObject(*BulletRO);
		SceneObjRef.SetComponentData(InData);
		World2D::Instance().AddPersistentObject(SceneObjRef, SOL_Layer2);
	}
}

void BasicAttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// Crazy88AttackComponent - Definition
// ----------------------------------------------------------------------------

Crazy88AttackComponent::Crazy88AttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void Crazy88AttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// BombAttackComponent - Definition
// ----------------------------------------------------------------------------

BombAttackComponent::BombAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void BombAttackComponent::Fire(float DeltaTime)
{

}

// ----------------------------------------------------------------------------
// BeamAttackComponent - Definition
// ----------------------------------------------------------------------------

BeamAttackComponent::BeamAttackComponent(ComponentData& InData)
	: AttackComponent(InData)
{
}

void BeamAttackComponent::Fire(float DeltaTime)
{

}

// EOF
