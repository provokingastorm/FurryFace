#ifndef TetrisBlockFactory_H_
#define TetrisBlockFactory_H_

#include "Defines.h"
#include "uncopyable.h"

struct Vector2D;


class TetrisBlockFactory : private Uncopyable
{
public:
    static class TetrisBlock* Create(EBlockType Type, const Vector2D& StartingPosition);

private:


};


#endif
