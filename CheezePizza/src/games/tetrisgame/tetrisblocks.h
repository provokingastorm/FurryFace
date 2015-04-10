#ifndef TetrisBlockS_H_
#define TetrisBlockS_H_

#include "tetrisblock.h"


class TetrisBlockS : public TetrisBlock
{
public:
    TetrisBlockS(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockS();
                        
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockS();
};

#endif

// EOF
