#include "cheezepizza.h"

// Papercraft
#include "papercraftstructures.h"
#include "papercraftplayership.h"

// Suppa bits
#include "sharedrenderables.h"
#include "world2d.h"
#include "scene2dobject.h"
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
	: CollisionComp(NULL)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	// Initialize ship data
	ShipData.Velocity = VelocityPerSec;

	// TEMP: Position the ship in the middle of the screen for testing
	const float ShipOriginX = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENWIDTH)) * 0.5f;
	const float ShipOriginY = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENHEIGHT)) * 0.5f;
	ShipData.X = ShipOriginX;
	ShipData.Y = ShipOriginY;

	ResetVelocity();

	// TEMP: Setting player's color to red. Player should be able to pick the color in the menus
	ShipData.PlayerColor = PC_Red;

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

 			ShipData.FacingDirX = (ShipTopPointX - ShipOriginX) / TopToOriginLength;
			ShipData.FacingDirY = (ShipTopPointY - ShipOriginY) / TopToOriginLength;
		}

		Ship->SetColor( GetPlayerColorFromInt(ShipData.PlayerColor) );

		StaticImage* ShipRO = new StaticImage();
		ShipRO->SetContent(*Ship);
		ShipRO->SetRotation(ShipRotation);

		ShipData.SceneData.RenderObject = ShipRO;
		Scene2DObject* ShipSceneObject = new Scene2DObject(ShipData.SceneData);
		//ShipSceneObject->SetRenderObject(*ShipRO);
		World2D::Instance().AddPersistentObject(*ShipSceneObject, SOL_Foreground);
	}
}

PapercraftPlayerShip::~PapercraftPlayerShip()
{
}

void PapercraftPlayerShip::Tick(float DeltaTime)
{
	if(ShipData.FireCooldownTimer > 0.0f)
	{
		ShipData.FireCooldownTimer -= DeltaTime;
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

void PapercraftPlayerShip::MoveHorizontal(float Scalar, float DeltaTime)
{
	ShipData.HorizontalMoveScalar = Scalar;

	const float VerticalMoveDelta = (ShipData.HorizontalMoveScalar * ShipData.Velocity.X * DeltaTime);
	ShipData.X = ShipData.X + VerticalMoveDelta;
}

void PapercraftPlayerShip::MoveVertical(float Scalar, float DeltaTime)
{
	ShipData.VeriticalMoveScalar = Scalar * -1.0f;

	const float HorizontalMoveDelta = (ShipData.VeriticalMoveScalar * ShipData.Velocity.Y * DeltaTime);
	ShipData.Y = ShipData.Y + HorizontalMoveDelta;
}

void PapercraftPlayerShip::ResetVelocity()
{
	ShipData.HorizontalMoveScalar = 0.0f;
	ShipData.VeriticalMoveScalar = 0.0f;
	ShipData.Velocity.X = VelocityPerSec;
	ShipData.Velocity.Y = VelocityPerSec;
}

void PapercraftPlayerShip::FirePrimaryWeapon(float DeltaTime)
{
}

void PapercraftPlayerShip::OnSetPartitionID(int PartitionID)
{
	if(CollisionComp != NULL)
	{
		CollisionComp->PartitonID = PartitionID;
	}
}

// EOF
