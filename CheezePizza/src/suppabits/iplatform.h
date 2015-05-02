#ifndef IPlatform_H_
#define IPlatform_H_

// ----------------------------------------------------------------------------
// IPlatform - Declaration
// ----------------------------------------------------------------------------

class IPlatform
{
public:

	virtual class HGE* GetHGE() const = 0;
	virtual class hgeResourceManager* GetResourceManager() const = 0;
};

#endif