#ifndef OriginsComponents_H_
#define OriginsComponents_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

#ifndef SharedComponents_H_
#include "sharedcomponents.h"
#endif

#ifndef DebugUtilities_H_
#include "debugutilities.h"
#endif

struct OriginsLinkComponentData : public ComponentData
{
	float X;
	float Y;
	float InvalidValue;

	OriginsLinkComponentData()
		: X(0.0f)
		, Y(0.0f)
		, InvalidValue(0.0f)
	{
	}

	float& operator[] (const int DataID)
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

		return InvalidValue;
	}

	const float& operator[] (const int DataID) const
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

		return InvalidValue;
	}

	bool SupportsData(int DataID)
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
			break;
		}

		return bSupports;
	}

	void SetInt(int DataID, int Data)
	{
	}

	void SetFloat(int DataID, float Data)
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
			break;
		}
	}

	void SetBool(int DataID, bool Data)
	{
	}

	virtual int GetInt(int DataID, int& DefaultValue)
	{
		return DefaultValue;
	}

	virtual float GetFloat(int DataID, float& DefaultValue)
	{
		float Data = DefaultValue;

		switch(DataID)
		{
		case CMPID_X:
			Data = X;
			break;

		case CMPID_Y:
			Data = Y;
			break;

		default:
			break;
		}

		return Data;
	}

	virtual bool GetBool(int DataID, bool& DefaultValue)
	{
		return DefaultValue;
	}
};



#endif