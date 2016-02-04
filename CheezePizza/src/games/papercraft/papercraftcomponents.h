#ifndef PapercraftComponents_H_
#define PapercraftComponents_H_

#ifndef Component_H_
#include "component.h"
#endif

#ifndef SharedComponents_H_
#include "sharedcomponents.h"
#endif


enum EPapercraftDataID
{
	PDID_Invalid	= 0,
	PDID_Shield		= CMPID_Max,
	PDID_Max
};


class PapercraftPlayerComponent : public Component
{
public:
	PapercraftPlayerComponent(class ComponentSystem& System);

private:
	PapercraftPlayerComponent();
};


#endif

// EOF
