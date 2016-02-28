#ifndef PapercraftComponentData_H_
#define PapercraftComponentData_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

#ifndef SharedComponents_H_
#include "sharedcomponents.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftComponentData - Enums
// ----------------------------------------------------------------------------

enum EPapercraftDataID
{
	PDID_Invalid	= 0,
	PDID_ShieldHP	= CMPID_Max,
	PDID_ShieldMax,
	PDID_Impulse,
	PDID_MissleCapacity,
	PDID_Turrets,
	PDID_RateOfFire,
	PDID_PlayerColor,
	PDID_Max
};

// ----------------------------------------------------------------------------
// PapercraftShipComponentData - Declaration
// ----------------------------------------------------------------------------

class PapercraftShipComponentData : public ComponentData
{
public:
	PapercraftShipComponentData();
	~PapercraftShipComponentData();

	virtual bool SupportsData(int DataID);

	int& Int(int DataIDa);
	const int& Int(int DataID) const;

	float& Float(int DataID);
	const float& Float(int DataID) const;

	bool& Bool(int DataID);
	const bool& Bool(int DataID) const;

private:

	float InvalidFloat;
	float X;
	float Y;
	float FacingDirX;
	float FacingDirY;
	float Impulse;

	int InvalidInt;
	int PlayerColor;

	bool InvalidBool;

private:
};

#endif

// EOF
