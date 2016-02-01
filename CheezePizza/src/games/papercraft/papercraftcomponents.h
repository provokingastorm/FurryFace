#ifndef PapercraftComponents_H_
#define PapercraftComponents_H_

#ifndef Component_H_
#include "component.h"
#endif


class PapercraftPlayerComponent : public Component
{
public:
	PapercraftPlayerComponent(class ComponentSystem& System);

private:
	PapercraftPlayerComponent();
};


#endif

// EOF
