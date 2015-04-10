#include "creditroll.h"
#include "gamecontrol.h"

extern int CreditRollStart(void);
extern int SlideShowDone(void);

int CreditRoll::Enter(GameControl *controller)
{
    //CreditRollStart();
    return 1;
}

int CreditRoll::Exit(GameControl *controller)
{
    return 1;
}

int CreditRoll::Update(GameControl *controller, float fDeltaTime)
{
    //if(SlideShowDone())
        //controller->ChangeState( GameControlState_Game );

    return 1;
}



