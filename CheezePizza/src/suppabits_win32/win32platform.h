#ifndef Win32Platform_H_
#define Win32Platform_H_

#ifndef IPlatform_H_
#include "iplatform.h"
#endif

// ----------------------------------------------------------------------------
// Win32Platform - Declaration
// ----------------------------------------------------------------------------

class Win32Platform : public IPlatform
{
public:
	Win32Platform();
	~Win32Platform();

	class HGE* GetHGE() const;
	class hgeResourceManager* GetResourceManager() const;

private:

	class HGE* HGEEngine;
	class hgeResourceManager* ResourceManager;
};

#endif