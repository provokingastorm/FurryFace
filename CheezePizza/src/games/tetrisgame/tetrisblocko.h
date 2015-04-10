#ifndef TetrisBlockO_H_
#define TetrisBlockO_H_

#include "tetrisblock.h"


class TetrisBlockO : public TetrisBlock
{
public:
    TetrisBlockO(float TopLeftPositionX, float TopLeftPositionY);
    ~TetrisBlockO();
                       
    int GetBottomLine() const;

protected:
    void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy);

private:
    TetrisBlockO();
};

#endif

// EOF
