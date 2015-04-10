#ifndef TetrisBlockZ_H_
#define TetrisBlockZ_H_

#include "tetrisblock.h"


class TetrisBlockZ : public TetrisBlock
{
public:
    TetrisBlockZ(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockZ();
                        
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockZ();
};

#endif

// EOF
