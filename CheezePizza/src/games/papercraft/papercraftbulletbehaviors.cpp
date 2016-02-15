#include "cheezepizza.h"
#include "papercraftbulletbehaviors.h"

#include "world2d.h"
#include "sharedrenderables.h"
#include "scene2dobject.h"

#include "cheezepizzaengine.h"
#include "hgeresource.h"

// ----------------------------------------------------------------------------
// BasicAttackComponent - Definition
// ----------------------------------------------------------------------------

class BasicShotRenderable : public IRenderable
{
public:

	BasicShotRenderable();
	~BasicShotRenderable();

	void AddAnimation(class hgeAnimation& InAnim);
	void AddBulletInstance(const Bullet& InBullet);

	void SetHotSpot(float X, float Y) { /* Intentionally blank because this object renders multiple bullets, not just one */ }

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void OnStart();
	void OnStop();
	void OnPause();

private:

	class hgeAnimation* CurrentAnim;
	std::vector<const Bullet*> BulletInstances;
};

BasicShotRenderable::BasicShotRenderable()
	: CurrentAnim(NULL)
{
}

BasicShotRenderable::~BasicShotRenderable()
{
	CurrentAnim = NULL;
}

void BasicShotRenderable::AddAnimation(hgeAnimation& InAnim)
{
	CurrentAnim = &InAnim;

	// Temp make this configurable
	DWORD Red = ARGB(255, 255, 0, 0);
	CurrentAnim->SetColor(Red);
}

void BasicShotRenderable::AddBulletInstance(const Bullet& InBullet)
{
	BulletInstances.push_back(&InBullet);
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
		const int NumBullets = BulletInstances.size();
		for(int i = 0; i < NumBullets; ++i)
		{
			CurrentAnim->Render(BulletInstances[i]->Position.X, BulletInstances[i]->Position.Y);
		}

		BulletInstances.clear();
	}
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
// PapercraftBulletBehavior - Definition
// ----------------------------------------------------------------------------

PapercraftBulletBehavior::PapercraftBulletBehavior()
	: Color(PBC_White)
{
}

// ----------------------------------------------------------------------------
// PapercraftBulletBehaviorDefault - Definition
// ----------------------------------------------------------------------------

PapercraftBulletBehaviorDefault::PapercraftBulletBehaviorDefault()
{
	Color = PBC_Red;

	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
	BulletAnim = CE.ResourceManager->GetAnimation("animBullet");

	if(BulletAnim != NULL)
	{
		BulletRO = new BasicShotRenderable();
		BulletRO->AddAnimation(*BulletAnim);

		BulletScene = new Scene2DObject();
		BulletScene->SetRenderObject(*BulletRO);

		World2D::Instance().AddPersistentObject(*BulletScene, SOL_Layer2);
	}
}

void PapercraftBulletBehaviorDefault::TickBullet(float DeltaTime, Bullet& ToTick)
{
	if(BulletRO != NULL)
	{
		ToTick.Position.Y += (30.0f * DeltaTime);
		BulletRO->AddBulletInstance(ToTick);
	}
}

// EOF
