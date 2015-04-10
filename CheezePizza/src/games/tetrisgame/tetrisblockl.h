#ifndef TetrisBlockL_H_
#define TetrisBlockL_H_

#include "tetrisblock.h"

class TetrisBlockL : public TetrisBlock
{
public:
    TetrisBlockL(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockL();

    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockL();
};


#endif

// EOF
