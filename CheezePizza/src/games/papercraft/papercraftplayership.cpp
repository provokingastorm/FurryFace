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
#include "collisioncomponent.h"

// Base engine
#include "cheezepizzaengine.h"
#include "hgeresource.h"

#include <math.h>

// ----------------------------------------------------------------------------
// PlayerShipCollisionCallback - Definition
// ----------------------------------------------------------------------------

class PlayerShipCollisionCallback : public CollisionCallback
{
public:

	PlayerShipCollisionCallback(PapercraftPlayerShip& InShip)
		: Ship(InShip)
	{
	}

	void OnCollision(const hgeRect& Other)
	{
	}

private:

	PlayerShipCollisionCallback();

	PapercraftPlayerShip& Ship;
};

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
	: BasicShotComp(NULL)
	, Crazy88ShotComp(NULL)
	, BombComp(NULL)
	, BeamComp(NULL)
	, TacComp(NULL)
	, CollisionComp(NULL)
	, Velocity(VelocityPerSec)
	, HorizontalMoveScalar(0.0f)
	, VeriticalMoveScalar(0.0f)
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

	// Create all the player's components
	BasicShotComp = new BasicAttackComponent(*SharedData);
	Crazy88ShotComp = new Crazy88AttackComponent(*SharedData);
	BombComp = new BombAttackComponent(*SharedData);
	BeamComp = new BeamAttackComponent(*SharedData);
	TacComp = new TacTriangleComponent(*SharedData);

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

	if(TacComp != NULL)
	{
		delete TacComp;
		TacComp = NULL;
	}
}

void PapercraftPlayerShip::PreTick(float DeltaTime)
{
	// Move the player's ship
	float& X = OwnerData->Float(CMPID_X);
	const float VerticalMoveDelta = (HorizontalMoveScalar * Velocity.X * DeltaTime);
	X = X + VerticalMoveDelta;

	float& Y = OwnerData->Float(CMPID_Y);
	const float HorizontalMoveDelta = (VeriticalMoveScalar * Velocity.Y * DeltaTime);
	Y = Y + HorizontalMoveDelta;
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
	if(CollisionComp == NULL)
	{
		CollisionComp = CollisionSubsystem::Instance().CreateCollisionComponent();

		if(CollisionComp != NULL)
		{
			CollisionComp->ChannelFlags = COLLISIONCHANNEL_01;
			CollisionComp->Callback = new PlayerShipCollisionCallback(*this);
		}
	}

	if(CollisionComp != NULL)
	{
		CollisionComp->bIsActive = true;
	}
}

void PapercraftPlayerShip::MoveHorizontal(float Scalar)
{
	HorizontalMoveScalar = Scalar;
}

void PapercraftPlayerShip::MoveVertical(float Scalar)
{
	VeriticalMoveScalar = Scalar;
}

void PapercraftPlayerShip::ResetVelocity()
{
	HorizontalMoveScalar = 0.0f;
	VeriticalMoveScalar = 0.0f;
	Velocity.X = VelocityPerSec;
	Velocity.Y = VelocityPerSec;
}

void PapercraftPlayerShip::FirePrimaryWeapon(float DeltaTime)
{
	if(BasicShotComp != NULL && FireCooldownTimer <= 0.0f)
	{
		BasicShotComp->Fire(DeltaTime);
		FireCooldownTimer = FireRate;
	}
}

void PapercraftPlayerShip::OnSetPartitionID(int PartitionID)
{
	if(CollisionComp != NULL)
	{
		CollisionComp->PartitonID = PartitionID;
	}
}

// EOF
