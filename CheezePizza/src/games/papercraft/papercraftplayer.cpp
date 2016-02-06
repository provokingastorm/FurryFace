#include "cheezepizza.h"

// Papercraft
#include "papercraftplayer.h"
#include "papercraftcomponents.h"
#include "papercraftcomponentdata.h"

// Suppa bits
#include "world2d.h"
#include "sharedrenderables.h"
#include "scene2dobject.h"
#include "componentdata.h"

// Base engine
#include "cheezepizzaengine.h"
#include "hgeresource.h"



// ----------------------------------------------------------------------------
// PapercraftPlayer - Static variables
// ----------------------------------------------------------------------------

const float PapercraftPlayer::VelocityPerSec = 135.0;
const float PapercraftPlayer::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

// ----------------------------------------------------------------------------
// PapercraftPlayer - Definition
// ----------------------------------------------------------------------------

PapercraftPlayer::PapercraftPlayer()
	: UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
{
}

PapercraftPlayer::~PapercraftPlayer()
{
	SceneObject = NULL;

	if(BasicShotComp != NULL)
	{
		delete BasicShotComp;
		BasicShotComp = NULL;
	}

	if(Crazy88ShotComp != NULL)
	{
		delete Crazy88ShotComp;
		Crazy88ShotComp = NULL;
	}

	if(BombComp != NULL)
	{
		delete BombComp;
		BombComp = NULL;
	}

	if(BeamComp != NULL)
	{
		delete BeamComp;
		BeamComp = NULL;
	}

	if(SharedData != NULL)
	{
		delete SharedData;
		SharedData = NULL;
	}
}

void PapercraftPlayer::OnCreatedInternal()
{
	// Setup the shared variables used by the components
	SharedData = new PapercraftShipComponentData();
	SharedData->Float(CMPID_X) = 100.0f;
	SharedData->Float(CMPID_Y) = 100.0f;

	// Create all the player's components
	BasicShotComp = new BasicAttackComponent(*SharedData);
	Crazy88ShotComp = new Crazy88AttackComponent(*SharedData);
	BombComp = new BombAttackComponent(*SharedData);
	BeamComp = new BeamAttackComponent(*SharedData);

	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
	hgeSprite* Ship = CE.ResourceManager->GetSprite("sprIdleShip");
	if(Ship != NULL)
	{
		StaticImage* ShipRO = new StaticImage();
		ShipRO->SetContent(*Ship);

		SceneObject = new Scene2DObject();
		SceneObject->SetRenderObject(*ShipRO);
		SceneObject->SetComponentData(*SharedData);
		World2D::Instance().AddPersistentObject(*SceneObject, SOL_Foreground);
	}
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SharedData->Float(CMPID_Y);
		const float MoveDelta = (UpVelocity * DeltaTime);
		Y = Y - MoveDelta;
	}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SharedData->Float(CMPID_Y);
		const float MoveDelta = (DownVelocity * DeltaTime);
		Y = Y + MoveDelta;
	}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SharedData->Float(CMPID_X);
		const float MoveDelta = (LeftVelocity * DeltaTime);
		X = X - MoveDelta;
	}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SharedData->Float(CMPID_X);
		const float MoveDelta = (RightVelocity * DeltaTime);
		X = X + MoveDelta;
	}
}

void PapercraftPlayer::ResetVelocity()
{
	UpVelocity = VelocityPerSec;
	DownVelocity = VelocityPerSec;
	LeftVelocity = VelocityPerSec;
	RightVelocity = VelocityPerSec;
}

void PapercraftPlayer::FirePrimaryWeapon(float DeltaTime)
{
	if(BasicShotComp != NULL)
	{
		BasicShotComp->Fire(DeltaTime);
	}
}

// EOF
