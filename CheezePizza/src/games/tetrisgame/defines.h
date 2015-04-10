#ifndef TetrisDefines_H_
#define TetrisDefines_H_


/** The number of blocks in a Tetris block */
const int TetrisBlockSize = 4;

enum EBlockType 
{
    BlockType_T         = 0, 
    BlockType_S, 
    BlockType_Z, 
    BlockType_O, 
    BlockType_L, 
    BlockType_J, 
    BlockType_I, 
    BlockType_Total, 
    BlockType_None
};

#define BLUE    0xFF0000FF
#define WHITE   0xFFFFFFFF
#define BLACK   0xFF000000
#define YELLOW  0xFFFFFF00
#define GRAY    0xFFD4D3D3
#define GREEN   0xFF00FF00
#define ORANGE  0xFFFF8000
#define PINK    0xFFE180C0
#define PURPLE  0xFF800080
#define RED     0xFFFF0000


#endif
