#ifndef ComponentData_H_
#define ComponentData_H_

// ----------------------------------------------------------------------------
// ComponentData - Declaration
// ----------------------------------------------------------------------------

class ComponentData
{
public:

	virtual bool SupportsData(int DataID) = 0;

	virtual void SetInt(int DataID, int Data) = 0;
	virtual void GetInt(int DataID, int& DefaultValue) const = 0;

	virtual void SetFloat(int DataID, float Data) = 0;
	virtual void GetFloat(int DataID, float& DefaultValue) const = 0;

	virtual void SetBool(int DataID, bool Data) = 0;
	virtual void GetBool(int DataID, bool& DefaultValue) const = 0;
};

#endif