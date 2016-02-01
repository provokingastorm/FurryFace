#ifndef PapercraftComponentData_H_
#define PapercraftComponentData_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

class PapercraftShipComponentData : public ComponentData
{
public:
	PapercraftShipComponentData();

	bool SupportsData(int DataID);

	int& Int(int DataIDa);
	const int& Int(int DataID) const;

	float& Float(int DataID);
	const float& Float(int DataID) const;

	bool& Bool(int DataID);
	const bool& Bool(int DataID) const;

private:

	float X;
	float Y;

	float InvalidFloat;
	int InvalidInt;
	bool InvalidBool;

private:
};

#endif

// EOF
