#ifndef GameControl_H_
#define GameControl_H_

#ifndef FSMMachine_H_
#include "fsmmachine.h"
#endif 

class TetrisGameSession;
class AttractMode;
class CreditRoll;


enum EGameControlState 
{
    GameControlState_Default        = -1,
    GameControlState_MainMenu       = 0,
    GameControlState_Game           = 1,
    GameControlState_CreditRoll     = 2,
    GameControlState_AttractMode    = 3,
    GameControlState_Total
};




class GameControl
{
public:
   inline static GameControl& Instance()
   {
       if(!m_Instance)
           m_Instance = new GameControl();

        return *m_Instance;
   };

   int Initialize();
   int Update();
   int Shutdown();

   int ChangeState( EGameControlState NewState );

private:
    TetrisGameSession *         m_Game;
    AttractMode *               m_AttractMode;
    CreditRoll *                m_CreditRoll;
    FSMMachine<GameControl> *   m_FSM;

    static GameControl *        m_Instance;

   GameControl(const GameControl&);
   GameControl& operator=(const GameControl&);
   GameControl(void);
   ~GameControl(void);
};

#endif