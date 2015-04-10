#include "tetrisblockfactory.h"
#include "tetrisblocki.h"
#include "tetrisblockj.h"
#include "tetrisblockl.h"
#include "tetrisblocko.h"
#include "tetrisblocks.h"
#include "tetrisblockt.h"
#include "tetrisblockz.h"
#include "vector2d.h"



TetrisBlock* TetrisBlockFactory::Create(EBlockType Type, const Vector2D& StartingPosition)
{
    TetrisBlock* NewTetrisBlock;

    switch(Type)
    {
        case BlockType_T:
            NewTetrisBlock = new TetrisBlockT( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_S:
            NewTetrisBlock = new TetrisBlockS( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_Z:
            NewTetrisBlock = new TetrisBlockZ( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_O:
            NewTetrisBlock = new TetrisBlockO( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_L:
            NewTetrisBlock = new TetrisBlockL( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_J:
            NewTetrisBlock = new TetrisBlockJ( StartingPosition.X, StartingPosition.Y );
            break;
        case BlockType_I:
            NewTetrisBlock = new TetrisBlockI( StartingPosition.X, StartingPosition.Y );
            break;
    }

    return NewTetrisBlock;
}

// EOF
