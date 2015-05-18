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

void OriginsLinkComponentData::SetInt(int DataID, int Data)
{
	CPForceAssert("Invalid component data ID provided");
}

void OriginsLinkComponentData::SetFloat(int DataID, float Data)
{
	switch(DataID)
	{
	case CMPID_X:
		X = Data;
		break;

	case CMPID_Y:
		Y = Data;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}
}

void OriginsLinkComponentData::SetBool(int DataID, bool Data)
{
	CPForceAssert("Invalid component data ID provided");
}

void OriginsLinkComponentData::GetInt(int DataID, int& Value) const
{
	CPForceAssert("Invalid component data ID provided");
}

void OriginsLinkComponentData::GetFloat(int DataID, float& Value) const
{
	switch(DataID)
	{
	case CMPID_X:
		Value = X;
		break;

	case CMPID_Y:
		Value = Y;
		break;

	default:
		CPForceAssert("Invalid component data ID provided");
		break;
	}
}

void OriginsLinkComponentData::GetBool(int DataID, bool& Value) const
{
	CPForceAssert("Invalid component data ID provided");
}