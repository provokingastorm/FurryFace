#ifndef OriginsComponentData_H_
#define OriginsComponentData_H_

#ifndef ComponentData_H_
#include "componentdata.h"
#endif

class OriginsLinkComponentData : public ComponentData
{
public:

	OriginsLinkComponentData();

	bool SupportsData(int DataID);

	void SetInt(int DataID, int Data);
	void GetInt(int DataID, int& Value) const;

	void SetFloat(int DataID, float Data);
	void GetFloat(int DataID, float& Value) const;

	void SetBool(int DataID, bool Data);
	void GetBool(int DataID, bool& Value) const;

private:

	float X;
	float Y;

	float InvalidFloat;
	int InvalidInt;
};

#endif