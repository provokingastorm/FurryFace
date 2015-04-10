#ifndef FSMState_H_
#define FSMState_H_


template <class Entity>
class FSMState
{
public:
    FSMState() {};
    virtual ~FSMState() {};

    virtual int Enter( Entity * Entity) = 0;
    virtual int Exit( Entity * Entity) = 0;
    virtual int Update( Entity * Entity, float fDeltaTime) = 0;
private:
};


#endif