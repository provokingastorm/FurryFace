// GameControl.cpp
#include "gamecontrol.h"
#include "tetrisgamesession.h"
#include "attractmode.h"
#include "creditroll.h"


GameControl* GameControl::m_Instance = NULL;

GameControl::GameControl()
{
    m_FSM           = new FSMMachine<GameControl>(this);
    m_Game          = new TetrisGameSession();
    m_AttractMode   = new AttractMode();
    m_CreditRoll    = new CreditRoll();
} 

GameControl::~GameControl()
{
    if(m_FSM)
        delete m_FSM;

    if(m_Game)
        delete m_Game;

    if(m_AttractMode)
        delete m_AttractMode;

    if(m_CreditRoll)
        delete m_CreditRoll;

    if(m_Instance)
        delete m_Instance;
}

int GameControl::Initialize()
{
    m_FSM->AddState( GameControlState_AttractMode, m_AttractMode );
    //m_FSM->AddState( GameControlState_Game, m_Game );
    m_FSM->AddState( GameControlState_CreditRoll, m_CreditRoll );
    m_FSM->TransitionState( GameControlState_Game );

    return 0;
}

int GameControl::Shutdown()
{
    return 0;
}

int GameControl::Update()
{
#pragma message("WARNING: GameControl::Update needs a delta time update")
    float fDeltaTime = 0.0f;

    m_FSM->Update(fDeltaTime);

    return 1;
}

int GameControl::ChangeState( EGameControlState NewState )
{
    m_FSM->TransitionState( NewState );

    return 0;
}



