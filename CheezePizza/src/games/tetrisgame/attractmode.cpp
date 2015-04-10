#include "attractmode.h" 


AttractMode::AttractMode()
{

} 

int AttractMode::Enter(GameControl *controller)
{   
    return 1;
} 

int AttractMode::Exit(GameControl *controller)
{
    return 1;
}

int AttractMode::Update(GameControl *controller, float fDeltaTime)
{
    if(0)
        controller->ChangeState( GameControlState_Game );

    return 1;
}

