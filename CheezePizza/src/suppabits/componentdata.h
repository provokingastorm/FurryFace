#ifndef ComponentData_H_
#define ComponentData_H_

// ----------------------------------------------------------------------------
// ComponentData - Declaration
// ----------------------------------------------------------------------------

struct ComponentData
{
public:

	virtual bool SupportsData(int DataID) = 0;

	virtual float& operator[] (const int DataID) = 0;
	virtual const float& operator[] (const int DataID) const = 0;
};

#endif