#ifndef _TETRISBLOCK_H_
#define _TETRISBLOCK_H_

#include "defines.h"

class TetrisGrid;
class TetrisBlockProxy;
class Block;
class HGE;


class TetrisBlock
{
public:
    TetrisBlock();
    TetrisBlock( float TopLeftPositionX, float TopLeftPositionY );                                       
    virtual ~TetrisBlock();                 
    
    Block* BlockAt(int Index);                                // returns the block at the given index
    
    EBlockType GetBlockType() const { return m_BlockType; };       // returns the type of block
    
    void UpdateLine();                                      // calls the updateLine() function on the blocks in the tetris block
    
    void Render( HGE * hgeEngine ) const;

    void Rotate();                                              // abstract virtual method that rotates the blocks
    bool CanRotate(const TetrisGrid& InGrid);
    virtual int GetBottomLine() const = 0;                    // returns the line number of one of the base blocks
    
    void MoveRight();                                       // calls the moveRight() method for each block
    void MoveLeft();                                        // calls the moveLeft() method for each block
    void MoveDown();                                        // calls the moveDown() method for each block

    void AddBlocksToGrid( TetrisGrid& Grid );
    
protected:
    Block * m_Blocks[4];                                       // an array of blocks that makes up a tetris block
    
    int x, y;                                                   // x and y-coordinates of the initial block
    EBlockType m_BlockType;                                        // the type of the tetris block

    virtual void SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy) = 0;
               
    int m_Rotation;    // the rotation number the block is at (see rotate() for each derived class)
    
};


#endif
