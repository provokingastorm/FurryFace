#include "cheezepizza.h"
#include "originscomponentdata.h"
#include "sharedcomponents.h"


OriginsLinkComponentData::OriginsLinkComponentData()
	: X(0.0f)
	, Y(0.0f)
	, InvalidFloat(0.0f)
	, InvalidInt(0)
{
}

bool OriginsLinkComponentData::SupportsData(int DataID)
{
	bool bSupports = false;

	switch(DataID)
	{
	case CMPID_X:
		bSupports = true;
		break;

	case CMPID_Y:
		bSupports = true;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return bSupports;
}

bool& OriginsLinkComponentData::Bool(int DataID)
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidBool;
}

const bool& OriginsLinkComponentData::Bool(int DataID) const
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidBool;
}

int& OriginsLinkComponentData::Int(int DataID)
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidInt;
}

const int& OriginsLinkComponentData::Int(int DataID) const
{
	CPForceAssert("Invalid component data ID provided");
	return InvalidInt;
}

float& OriginsLinkComponentData::Float(int DataID)
{
	switch(DataID)
	{
	case CMPID_X:
		return X;
		break;

	case CMPID_Y:
		return Y;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidFloat;
}

const float& OriginsLinkComponentData::Float(int DataID) const
{
	switch(DataID)
	{
	case CMPID_X:
		return X;
		break;

	case CMPID_Y:
		return Y;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}

	return InvalidFloat;
}