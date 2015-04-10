#ifndef TetrisBlockJ_H_
#define TetrisBlockJ_H_

#include "tetrisblock.h"

class TetrisBlockJ : public TetrisBlock
{
public:
    TetrisBlockJ(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockJ();
                   
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockJ();

};

#endif

// EOF
