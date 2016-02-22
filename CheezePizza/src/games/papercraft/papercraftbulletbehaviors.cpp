#include "cheezepizza.h"
#include "papercraftbulletbehaviors.h"

#include "world2d.h"
#include "sharedrenderables.h"
#include "scene2dobject.h"

#include "cheezepizzaengine.h"
#include "hgerect.h"
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
	void AddBulletToRenderList(const Bullet& InBullet);

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
	BulletInstances.~vector();
	CurrentAnim = NULL;
}

void BasicShotRenderable::AddAnimation(hgeAnimation& InAnim)
{
	CurrentAnim = &InAnim;
}

void BasicShotRenderable::AddBulletToRenderList(const Bullet& InBullet)
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
			CurrentAnim->SetColor(BulletInstances[i]->Color);
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
	: Speed(0.0f)
{
}

PapercraftBulletBehavior::~PapercraftBulletBehavior()
{
}

// ----------------------------------------------------------------------------
// PapercraftBulletBehaviorDefault - Definition
// ----------------------------------------------------------------------------

PapercraftBulletBehaviorDefault::PapercraftBulletBehaviorDefault()
{
	Speed = 1024.0f;

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

PapercraftBulletBehaviorDefault::~PapercraftBulletBehaviorDefault()
{
	// All of these object lifetimes are managed by World2D or the engine
	BulletRO = NULL;
	BulletScene = NULL;
	BulletAnim = NULL;
}

void PapercraftBulletBehaviorDefault::TickBullet(float DeltaTime, Bullet& ToTick)
{
	if(BulletRO != NULL)
	{
		float SpeedThisFrame = Speed * DeltaTime;
		ToTick.Position.X += (ToTick.Direction.X * SpeedThisFrame);
		ToTick.Position.Y += (ToTick.Direction.Y * SpeedThisFrame);

		// Update the world bounds for the collision system
		BulletAnim->GetBoundingBox(ToTick.Position.X, ToTick.Position.Y, &ToTick.WorldBounds);

		BulletRO->AddBulletToRenderList(ToTick);
	}
}

bool PapercraftBulletBehaviorDefault::IsBulletOffScreen(const Bullet& TestBullet) const
{
	HGE& HGEEngine = CheezePizzaEngine::Instance().GetHGE();

	const float ScreenWidth = static_cast<float>(HGEEngine.System_GetState(HGE_SCREENWIDTH));
	const float ScreenHeight = static_cast<float>(HGEEngine.System_GetState(HGE_SCREENHEIGHT));
	hgeRect ScreenRect(0.0f, 0.0f, ScreenWidth, ScreenHeight);

	hgeRect BulletRect;
	BulletAnim->GetBoundingBox(TestBullet.Position.X, TestBullet.Position.Y, &BulletRect);

	// A bullet is fully-off-screen when its collision rect is outside the screen rect
	return !ScreenRect.Intersect(&BulletRect);
}

// EOF
