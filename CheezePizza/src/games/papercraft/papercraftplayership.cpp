#include "cheezepizza.h"

// Papercraft
#include "papercraftstructures.h"
#include "papercraftplayership.h"
#include "papercraftcomponents.h"
#include "papercraftcomponentdata.h"

// Suppa bits
#include "sharedrenderables.h"
#include "componentdata.h"
#include "collisionsubsystem.h"

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
	PapercraftShipComponentData* SharedData = new PapercraftShipComponentData();

	// TEMP: Position the ship in the middle of the screen for testing
	const float ShipOriginX = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENWIDTH)) * 0.5f;
	const float ShipOriginY = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENHEIGHT)) * 0.5f;
	SharedData->Float(CMPID_X) = ShipOriginX;
	SharedData->Float(CMPID_Y) = ShipOriginY;

	// TEMP: Setting player's color to red. Player should be able to pick the color in the menus
	SharedData->Int(PDID_PlayerColor) = PC_Red;

	// Setup the player's collision component
	CollisionComp = new CollisionComponent();

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
		{
			// The default orientation of the ship is pointing straight up. To calculate the facing direction, 
			// we can figure out the point at the top of the ship and use the origin to calculate the direction vector. 
			// Unfortunately, we have to factor in the rotation of the ship to find the point at the top of the ship image.
			// We will rotate around the origin (i.e. middle of the image - aka hotspot) in local coordinate space. 
			// Fortunately, we can take a shortcut without figuring out the top point. Since the origin is in the middle of 
			// the ship, we only need to divide the height in half to get the result of the subtraction of both points.
			// Also, multiply by -0.5 instead of 0.5 because the Y-coordinate is inverted in screen coordinates.
			const float VerticalDifference = Ship->GetHeight() * -0.5f;

			// Since there is no horizontal translation between the two points, don't factor the X-component in the calculation.
			float ShipTopPointX = /*  X*Cosine  */ - VerticalDifference * sin(ShipRotation);
			float ShipTopPointY = /*  X*Sine +  */ VerticalDifference * cos(ShipRotation);

			// Translate the rotated point from local space to world space
 			ShipTopPointX += ShipOriginX;
			ShipTopPointY += ShipOriginY;

			// Now, figure out the facing direction 
			const float TopToOriginLength = sqrt((ShipTopPointX*ShipTopPointY) + (ShipOriginX*ShipOriginY));

 			SharedData->Float(CMPID_FacingDirX) = (ShipTopPointX - ShipOriginX) / TopToOriginLength;
			SharedData->Float(CMPID_FacingDirY) = (ShipTopPointY - ShipOriginY) / TopToOriginLength;
		}

		Ship->SetColor( GetPlayerColorFromInt(SharedData->Int(PDID_PlayerColor)) );

		StaticImage* ShipRO = new StaticImage();
		ShipRO->SetContent(*Ship);
		ShipRO->SetRotation(ShipRotation);

		SetRenderObject(*ShipRO);
		SetComponentData(*SharedData);
	}
}

PapercraftPlayerShip::~PapercraftPlayerShip()
{
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
}

void PapercraftPlayerShip::Tick(float DeltaTime)
{
	Scene2DObject::Tick(DeltaTime);

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

void PapercraftPlayerShip::RegisterCollisionComponent()
{
	if(CollisionComp != NULL)
	{
		CollisionSubsystem::Instance().AddCollisionComponent(CollisionComp);
	}
}

void PapercraftPlayerShip::MoveUp(float DeltaTime)
{
	float& Y = OwnerData->Float(CMPID_Y);
	const float MoveDelta = (UpVelocity * DeltaTime);
	Y = Y - MoveDelta;
}

void PapercraftPlayerShip::MoveDown(float DeltaTime)
{
	float& Y = OwnerData->Float(CMPID_Y);
	const float MoveDelta = (DownVelocity * DeltaTime);
	Y = Y + MoveDelta;
}

void PapercraftPlayerShip::MoveLeft(float DeltaTime)
{
	float& X = OwnerData->Float(CMPID_X);
	const float MoveDelta = (LeftVelocity * DeltaTime);
	X = X - MoveDelta;
}

void PapercraftPlayerShip::MoveRight(float DeltaTime)
{
	float& X = OwnerData->Float(CMPID_X);
	const float MoveDelta = (RightVelocity * DeltaTime);
	X = X + MoveDelta;
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
