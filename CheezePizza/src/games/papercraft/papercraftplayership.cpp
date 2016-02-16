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

#include <math.h>

// ----------------------------------------------------------------------------
// PapercraftPlayerShip - Static variables
// ----------------------------------------------------------------------------

const float PapercraftPlayerShip::VelocityPerSec = 135.0;
const float PapercraftPlayerShip::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;
const float FireRate = 0.5f;

// ----------------------------------------------------------------------------
// PapercraftPlayerShip - Definition
// ----------------------------------------------------------------------------

PapercraftPlayerShip::PapercraftPlayerShip()
	: UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
	, FireCooldownTimer(0.0f)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	// Setup the shared variables used by the components
	SharedData = new PapercraftShipComponentData();

	// TEMP: Position the ship in the middle of the screen for testing
	const float ShipOriginX = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENWIDTH)) * 0.5f;
	const float ShipOriginY = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENHEIGHT)) * 0.5f;
	SharedData->Float(CMPID_X) = ShipOriginX;
	SharedData->Float(CMPID_Y) = ShipOriginY;

	// Create all the player's components
	BasicShotComp = new BasicAttackComponent(*SharedData);
	Crazy88ShotComp = new Crazy88AttackComponent(*SharedData);
	BombComp = new BombAttackComponent(*SharedData);
	BeamComp = new BeamAttackComponent(*SharedData);

	hgeSprite* Ship = CE.ResourceManager->GetSprite("sprIdleShip");
	if(Ship != NULL)
	{
		const float ShipRotation = CheezePizzaEngine::Instance().GetHGE().Random_Float(0, M_PI * 2);

		// Calculate the ship's facing direction
		const float Cosine = cos(ShipRotation);
		const float Sine = sin(ShipRotation);

		// The default orientation of the ship is pointing straight up. To calculate the facing direction, 
		// we can figure out the point at the top of the ship and use the origin to calculate the direction vector. 
		// Unfortunately, we have to factor in the rotation of the ship to find the point at the top of the ship image.
		// We will rotate around the origin (i.e. middle of the image - aka hotspot) in local coordinate space. 
		// Fortunately, we can take a shortcut without figuring out the top point. Since the origin is in the middle of 
		// the ship, we only need to divide the height in half to get the result of the subtraction of both points.
		// Also, multiply by -0.5 instead of 0.5 because the Y-coordinate is inverted in screen coordinates.
		const float VerticalDifference = Ship->GetHeight() * -0.5f;

		// Since there is no horizontal translation between the two points, don't factor the X-component in the calculation.
		float TopPointX = /*  X*Cosine  */ - VerticalDifference * Sine;
		float TopPointY = /*  X*Sine +  */ VerticalDifference * Cosine;

		// Translate the rotated point from local space to world space
 		TopPointX += ShipOriginX;
		TopPointY += ShipOriginY;

		// Now, figure out the facing direction 
		const float DirectionLength = sqrt((TopPointX*TopPointY) + (ShipOriginX*ShipOriginY));

 		SharedData->Float(CMPID_FacingDirX) = (TopPointX - ShipOriginX) / DirectionLength;
		SharedData->Float(CMPID_FacingDirY) = (TopPointY - ShipOriginY) / DirectionLength;

		StaticImage* ShipRO = new StaticImage();
		ShipRO->SetContent(*Ship);
		ShipRO->SetRotation(ShipRotation);

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
	if(FireCooldownTimer > 0.0f)
	{
		FireCooldownTimer -= DeltaTime;
	}

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
	if(BasicShotComp != NULL && FireCooldownTimer <= 0.0f)
	{
		BasicShotComp->Fire(DeltaTime);
		FireCooldownTimer = FireRate;
	}
}

// EOF
