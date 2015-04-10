#ifndef TetrisBlockI_H_
#define TetrisBlockI_H_

#include "tetrisblock.h"

class TetrisBlockI : public TetrisBlock
{
public:
    TetrisBlockI(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockI();
                         
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockI();
};

#endif

// EOF
