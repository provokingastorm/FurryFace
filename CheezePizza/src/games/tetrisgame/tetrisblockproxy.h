#ifndef TetrisBlockProxy_H_
#define TetrisBlockProxy_H_

#include "defines.h"
#include "vector2d.h"

class Block;
class TetrisGrid;

struct BlockProxy
{
public:
    BlockProxy()
    {
    }

    BlockProxy( Vector2D Coordinates, int InLine, int InLinePosition )
        :   Position(Coordinates)
        ,   Line(InLine)
        ,   LinePosition(InLinePosition)
    {
    }

    Vector2D	Position;
    int			Line;
    int			LinePosition;
};


class TetrisBlockProxy
{
public:
    TetrisBlockProxy(Block* Blocks[TetrisBlockSize]);
    ~TetrisBlockProxy();

    bool WillBlocksCollideWithGrid(const TetrisGrid& InGrid);

	// TO DO: Make me private
    BlockProxy  Proxies[TetrisBlockSize];

private:

private:
    TetrisBlockProxy();

};


#endif