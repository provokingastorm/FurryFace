#ifndef TetrisBlockT_H_
#define TetrisBlockT_H_

#include "tetrisblock.h"

class TetrisBlockT : public TetrisBlock
{
public:
    TetrisBlockT(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockT();
                   
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockT();
};

#endif

// EOF
