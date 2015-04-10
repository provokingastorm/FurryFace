#ifndef TetrisGrid_H_
#define TetrisGrid_H_

struct CompletedLineEvent;
class Line;
class TetrisBlock;
class Block;
class HGE;

static const int TetrisGridSize = 20;

enum ETetrisGridError
{
    TetrisGridError_Failed        = 0,
    TetrisGridError_Success       = 1
};



/**
 * @author Peter Bennett (curlyhairedgreatness@gmail.com)
 */
class TetrisGrid
{

private:

    Line* 			m_BlockLines[TetrisGridSize];
    mutable int     m_FirstCompletedLineIndex;
    bool            m_LogCompletedBlocks;

public:

    TetrisGrid();
    ~TetrisGrid();
 
    int     ClearCompletedLines();
    void    Render( HGE * hgeEngine ) const;

    int     GetLinesCompleted() const;
    void    SnapTetrisBlockToGrid(TetrisBlock& CurrentBlock);
    void    AddBlockToGrid(Block& BlockToAdd, int Line, int Position);
    bool    IsBlockAtPosition(int Line, int Position) const;
	bool	IsBlockOutsideGrid(int Line, int Position) const;

    // Collision Detection
    bool    WillCollideWithBase( TetrisBlock * CurrentBlock );
    bool    WillCollideWithTop( TetrisBlock * CurrentBlock );
    bool    WillCollideWithRightWall( TetrisBlock * CurrentBlock );
    bool    WillCollideWithLeftWall( TetrisBlock * CurrentBlock );
    bool    WillCollideWithGrid( TetrisBlock * CurrentBlock );

private:

    void            ClearLine(int Index);
    virtual void    OnLineComplete(const CompletedLineEvent& EventRecord);

#if defined TETRIS_GRID_LOG
    void            DebugRender(bool BeforeLineDelete) const;
    void            LogCompletedEvent(const CompletedLineEvent& EventRecord);
#endif
};




#endif