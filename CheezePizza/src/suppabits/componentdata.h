#ifndef ComponentData_H_
#define ComponentData_H_

// ----------------------------------------------------------------------------
// ComponentData - Declaration
// ----------------------------------------------------------------------------

class ComponentData
{
public:

	virtual bool SupportsData(int DataID) = 0;

	virtual int& Int(int DataID) = 0;
	virtual const int& Int(int DataID) const = 0;

	virtual float& Float(int DataID) = 0;
	virtual const float& Float(int DataID) const = 0;

	virtual bool& Bool(int DataID) = 0;
	virtual const bool& Bool(int DataID) const = 0;
};

#endif