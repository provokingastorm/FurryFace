#ifndef AttractMode_H_
#define AttractMode_H_

#ifndef FSMState_H_
#include "fsmstate.h"
#endif

#ifndef GameControl_H_
#include "gamecontrol.h"
#endif

class AttractMode : public FSMState<GameControl>
{
public:
   AttractMode();
   ~AttractMode() {};

    int Enter(GameControl *controller);
    int Exit(GameControl *controller);
    int Update(GameControl *controller, float fDeltaTime);

private:
}; 

#endif
