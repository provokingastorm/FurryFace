#ifndef _CREDITROLL_H_
#define _CREDITROLL_H_

#ifndef _FSMSTATE_H_
#include "fsmstate.h"
#endif

class GameControl;

class CreditRoll : public FSMState<GameControl>
{
public:
    CreditRoll() {};
    ~CreditRoll() {};

    int Enter(GameControl *controller);
    int Exit(GameControl *controller);
    int Update(GameControl *controller, float fDeltaTime);
};


#endif