#ifndef PapercraftPlayerHandler_H_
#define PapercraftPlayerHandler_H_

#ifndef ActionHandler_H_
#include "actionhandler.h"
#endif


class PapercraftPlayerHandler : public ActionHandler
{
public:

	PapercraftPlayerHandler();
	~PapercraftPlayerHandler();

	void SetShip(class PapercraftPlayerShip& InShip);

private:

	class PapercraftPlayerShip* Ship;
};

#endif

// EOF
