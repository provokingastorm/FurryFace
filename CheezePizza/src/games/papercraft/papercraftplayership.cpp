#include "cheezepizza.h"

// Papercraft
#include "papercraftplayership.h"
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
// PapercraftPlayerShip - Static variables
// ----------------------------------------------------------------------------

const float PapercraftPlayerShip::VelocityPerSec = 135.0;
const float PapercraftPlayerShip::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

// ----------------------------------------------------------------------------
// PapercraftPlayerShip - Definition
// ----------------------------------------------------------------------------

PapercraftPlayerShip::PapercraftPlayerShip()
	: UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	// Setup the shared variables used by the components
	SharedData = new PapercraftShipComponentData();

	// TEMP: Position the ship in the middle of the screen for testing
	SharedData->Float(CMPID_X) = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENWIDTH)) * 0.5f;
	SharedData->Float(CMPID_Y) = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENHEIGHT)) * 0.5f;

	// Create all the player's components
	BasicShotComp = new BasicAttackComponent(*SharedData);
	Crazy88ShotComp = new Crazy88AttackComponent(*SharedData);
	BombComp = new BombAttackComponent(*SharedData);
	BeamComp = new BeamAttackComponent(*SharedData);

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

PapercraftPlayerShip::~PapercraftPlayerShip()
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

void PapercraftPlayerShip::Tick(float DeltaTime)
{
	if(BasicShotComp != NULL)
	{
		BasicShotComp->Tick(DeltaTime);
	}

	if(Crazy88ShotComp != NULL)
	{
		Crazy88ShotComp->Tick(DeltaTime);
	}

	if(BombComp != NULL)
	{
		BombComp->Tick(DeltaTime);
	}

	if(BeamComp != NULL)
	{
		BeamComp->Tick(DeltaTime);
	}
}

void PapercraftPlayerShip::OnTickStarted()
{
}

void PapercraftPlayerShip::OnTickStopped()
{
}

void PapercraftPlayerShip::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SharedData->Float(CMPID_Y);
		const float MoveDelta = (UpVelocity * DeltaTime);
		Y = Y - MoveDelta;
	}
}

void PapercraftPlayerShip::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SharedData->Float(CMPID_Y);
		const float MoveDelta = (DownVelocity * DeltaTime);
		Y = Y + MoveDelta;
	}
}

void PapercraftPlayerShip::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SharedData->Float(CMPID_X);
		const float MoveDelta = (LeftVelocity * DeltaTime);
		X = X - MoveDelta;
	}
}

void PapercraftPlayerShip::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SharedData->Float(CMPID_X);
		const float MoveDelta = (RightVelocity * DeltaTime);
		X = X + MoveDelta;
	}
}

void PapercraftPlayerShip::ResetVelocity()
{
	UpVelocity = VelocityPerSec;
	DownVelocity = VelocityPerSec;
	LeftVelocity = VelocityPerSec;
	RightVelocity = VelocityPerSec;
}

void PapercraftPlayerShip::FirePrimaryWeapon(float DeltaTime)
{
	if(BasicShotComp != NULL)
	{
		BasicShotComp->Fire(DeltaTime);
	}
}

// EOF
