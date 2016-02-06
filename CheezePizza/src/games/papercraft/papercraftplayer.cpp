#include "cheezepizza.h"
#include "papercraftplayer.h"
#include "papercraftcomponents.h"
#include "papercraftcomponentdata.h"
#include "scene2dobject.h"
#include "sharedrenderables.h"
#include "scene2dobject.h"
#include "componentdata.h"
#include "cheezepizzaengine.h"
#include "world2d.h"
#include "hgeresource.h"

const float PapercraftPlayer::VelocityPerSec = 135.0;
const float PapercraftPlayer::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

PapercraftPlayer::PapercraftPlayer()
	: UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
{
	// Setup the shared variables used by the components
	SharedData = new PapercraftShipComponentData();
	PapercraftShipComponentData& ShipData = *SharedData;
	ShipData.Float(CMPID_X) = 100.0f;
	ShipData.Float(CMPID_Y) = 100.0f;

	// Create all the player's components
	BasicShotComp = new BasicAttackComponent(ShipData);
	Crazy88ShotComp = new Crazy88AttackComponent(ShipData);
	BombComp = new BombAttackComponent(ShipData);
	BeamComp = new BeamAttackComponent(ShipData);

	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
	hgeSprite* Ship = CE.ResourceManager->GetSprite("sprIdleShip");
	if(Ship != NULL)
	{
		StaticImage* ShipRO = new StaticImage();
		ShipRO->SetContent(*Ship);

		SceneObject = new Scene2DObject();
		Scene2DObject& SceneObjRef = *SceneObject;
		SceneObjRef.SetRenderObject(*ShipRO);
		SceneObjRef.SetComponentData(ShipData);
		World2D::Instance().AddPersistentObject(SceneObjRef, SOL_Foreground);
	}
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

void PapercraftPlayer::AssociateSceneObject(Scene2DObject& PlayerObject)
{
	SceneObject = &PlayerObject;
}

void PapercraftPlayer::DisassociateSceneObject()
{
	SceneObject = NULL;
}

void PapercraftPlayer::OnCreatedInternal()
{
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SceneObject->GetData().Float(CMPID_Y);
		const float MoveDelta = (UpVelocity * DeltaTime);
		Y = Y - MoveDelta;
	}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SceneObject->GetData().Float(CMPID_Y);
		const float MoveDelta = (DownVelocity * DeltaTime);
		Y = Y + MoveDelta;
	}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SceneObject->GetData().Float(CMPID_X);
		const float MoveDelta = (LeftVelocity * DeltaTime);
		X = X - MoveDelta;
	}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SceneObject->GetData().Float(CMPID_X);
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

}

// EOF
