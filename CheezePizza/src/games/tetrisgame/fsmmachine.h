#ifndef FSMMachine_H_
#define FSMMachine_H_

#ifndef FSMState_H_
#include "fsmstate.h"
#endif

#ifndef StdMap_H_
#define StdMap_H_
#include <map>
#endif

#ifndef Compares_H_
#include "compares.h"
#endif



template <class Entity>
class FSMMachine
{
public:
    FSMMachine(Entity *owner)
        :   m_Owner(owner), 
            m_CurrentState(NULL), 
            m_PreviousState(NULL) 
    {  };

    ~FSMMachine() {};

    int TransitionState( int ID);
    int AddState( int ID, FSMState<Entity> * State );
    int Update( float fDeltaTime);

private:
    Entity *            m_Owner;
    FSMState<Entity> *  m_CurrentState;
    FSMState<Entity> *  m_PreviousState;

    typedef std::map<int, FSMState<Entity>*, IntCompare> StateMap;
    StateMap            m_States;

private:
    FSMMachine();
    FSMMachine& operator=(const FSMMachine &);
    FSMMachine(const FSMMachine &);
    
};


template <class Entity>
int FSMMachine<Entity>::AddState(int id, FSMState<Entity> *state)
{
    int isSuccessful = 0;

    StateMap::iterator iterator = m_States.find(id);

    if(iterator == m_States.end())
    {
        m_States[id] = state;
        isSuccessful = 1;
    }

    return isSuccessful;
}

/**
 * Transitions the current state to the given state (id).
 * 
 * @remarks This routine stores the current state as
 * the previous state. The ID is defined by the owner of the FSM.
 * 
 * @param id The ID of the state that will replace the current state. 
 *
 * @return true if state successfully transitioned; false, otherwise.
 */
template <class Entity>
int FSMMachine<Entity>::TransitionState(int id)
{
    StateMap::iterator iterator = m_States.find(id);
    if(iterator == m_States.end())
        return 0;

    m_PreviousState = m_CurrentState;

    if(m_CurrentState)
        m_CurrentState->Exit(m_Owner);

    m_CurrentState = (*iterator).second;
    m_CurrentState->Enter(m_Owner);

    return 1;
}
template <class Entity>
int FSMMachine<Entity>::Update(float deltaTime)
{
    if(m_CurrentState)
        m_CurrentState->Update(m_Owner, deltaTime);

    return 0;
}
#endif