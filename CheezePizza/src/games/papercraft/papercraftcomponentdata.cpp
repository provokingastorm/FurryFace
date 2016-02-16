#include "cheezepizza.h"
#include "papercraftcomponentdata.h"
#include "sharedcomponents.h"

// ----------------------------------------------------------------------------
// PapercraftShipComponentData - Definition
// ----------------------------------------------------------------------------

PapercraftShipComponentData::PapercraftShipComponentData()
	: InvalidFloat(0.0f)
	, X(0.0f)
	, Y(0.0f)
	, FacingDirX(0.0f)
	, FacingDirY(0.0f)
	, Impulse(0.0f)
	, InvalidInt(0)
	, PlayerColor(0)
	, InvalidBool(false)
{
}

bool PapercraftShipComponentData::SupportsData(int DataID)
{
	bool bSupports = false;

	switch(DataID)
	{
	case CMPID_X:
	case CMPID_Y:
	case CMPID_FacingDirX:
	case CMPID_FacingDirY:
	case PDID_Impulse:
	case PDID_PlayerColor:
		bSupports = true;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return bSupports;
}

bool& PapercraftShipComponentData::Bool(int DataID)
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidBool;
}

const bool& PapercraftShipComponentData::Bool(int DataID) const
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidBool;
}

int& PapercraftShipComponentData::Int(int DataID)
{
	switch(DataID)
	{
	case PDID_PlayerColor:
		return PlayerColor;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidInt;
}

const int& PapercraftShipComponentData::Int(int DataID) const
{
	switch(DataID)
	{
	case PDID_PlayerColor:
		return PlayerColor;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidInt;
}

float& PapercraftShipComponentData::Float(int DataID)
{
	switch(DataID)
	{
	case CMPID_X:
		return X;
		break;

	case CMPID_Y:
		return Y;
		break;

	case CMPID_FacingDirX:
		return FacingDirX;
		break;

	case CMPID_FacingDirY:
		return FacingDirY;
		break;

	case PDID_Impulse:
		return Impulse;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidFloat;
}

const float& PapercraftShipComponentData::Float(int DataID) const
{
	switch(DataID)
	{
	case CMPID_X:
		return X;
		break;

	case CMPID_Y:
		return Y;
		break;

	case CMPID_FacingDirX:
		return FacingDirX;
		break;

	case CMPID_FacingDirY:
		return FacingDirY;
		break;

	case PDID_Impulse:
		return Impulse;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidFloat;
}

// EOF
