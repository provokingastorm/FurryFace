#include "cheezepizza.h"
#include "papercraftcomponentdata.h"
#include "sharedcomponents.h"

PapercraftShipComponentData::PapercraftShipComponentData()
	: X(0.0f)
	, Y(0.0f)
	, Impulse(0.0f)
	, InvalidFloat(0.0f)
	, InvalidInt(0)
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
	case PDID_Impulse:
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
	InvalidBool = false;
	return InvalidBool;
}

const bool& PapercraftShipComponentData::Bool(int DataID) const
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidBool;
}

int& PapercraftShipComponentData::Int(int DataID)
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidInt;
}

const int& PapercraftShipComponentData::Int(int DataID) const
{
	CPForceAssert("Invalid component data ID provided");
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
