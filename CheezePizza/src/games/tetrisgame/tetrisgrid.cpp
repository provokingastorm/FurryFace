#include "tetrisgrid.h"
#include "line.h"
#include "tetrisblock.h"
#include "block.h"
#include "debugutilities.h"
#include "cheezepizzaengine.h"

#if defined TETRIS_GRID_LOG
#include "CPString.h"
#endif

/** Defines the Index of m_BlockLines which is considered the left bounds */
#define LEFT_MOST_GRID_INDEX    0
/** Defines the Index of m_BlockLines which is considered the right bounds */
#define RIGHT_MOST_GRID_INDEX   9


struct CompletedLineEvent
{
    CompletedLineEvent( int NumberOfLines, int FirstLineCompletedIndex )
        :   LinesCompleted(NumberOfLines),
            InitialLineToShiftDown(FirstLineCompletedIndex)
    {
    }

    int     LinesCompleted;
    int     InitialLineToShiftDown;
};


////////////////////////////////////////////////////////////////////////////////////////////
// Default Constructor
////////////////////////////////////////////////////////////////////////////////////////////
TetrisGrid::TetrisGrid()
    :   m_FirstCompletedLineIndex(-1),
        m_LogCompletedBlocks(false)
{
    for( int Index = 0; Index <= 20; ++Index )
    {
        m_BlockLines[Index] = new Line();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////
TetrisGrid::~TetrisGrid()
{
    for( int Index = 0; Index <= 20; ++Index )
    {
        if( m_BlockLines[Index] )
            m_BlockLines[Index
            ] = new Line();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Deletes any completed lines and shifting the rest of the lines down.
 *
 * @remarks This function does <b>not</b> report the 
 * number of completed lines. See TetrisGrid::LinesCompleted.
 *
 * @return An error message. See ETetrisGridUpdateError
 */
////////////////////////////////////////////////////////////////////////////////////////////
int TetrisGrid::ClearCompletedLines()
{
    int Result                      = TetrisGridError_Failed;
    int LineArrayIndex              = 0;
    int LinesCompleted              = 0;
    int FirstLineCompletedIndex     = -1;
    bool bFoundFirstCompletedLine   = false;
    bool bNoMoreCompletedLines      = false;

    // Iterate through lines from bottom to top to avoid wasted CPU cycles
    // if we know that there won't be any more completed lines
    while( (LineArrayIndex < 20) && (bNoMoreCompletedLines == false) )
    {
        if( !bFoundFirstCompletedLine )
        {
            if( m_BlockLines[LineArrayIndex]->IsFilled() )
            {
#if defined TETRIS_GRID_LOG
                DebugRender(true);
#endif
                bFoundFirstCompletedLine = true;
                FirstLineCompletedIndex = LineArrayIndex;
                ++LinesCompleted;
                Result = TetrisGridError_Success;
                ClearLine( LineArrayIndex );
            }
        }
        // We have at least one line completed. The previous line is completed.
        // Is the line above it filled too?
        else
        {
            if( m_BlockLines[LineArrayIndex]->IsFilled() )
            {
#if defined TETRIS_GRID_LOG
                DebugRender(true);
#endif
                ++LinesCompleted;
                ClearLine( LineArrayIndex );
            }
            // On the first occurance of not finding a completed line when at
            // least one completed line was previously discovered, make sure
            // we stop checking for completed lines because it's not possible. 
            else
                bNoMoreCompletedLines = true;
        }

        ++LineArrayIndex;
    }

    if( bFoundFirstCompletedLine )
    {
        CompletedLineEvent EventRecord(LinesCompleted, FirstLineCompletedIndex + LinesCompleted);
        OnLineComplete(EventRecord);
    }
    
#if defined TETRIS_GRID_LOG
    DebugRender(false);
#endif

    return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Renders all graphical elements in the Grid
 *
 * @remarks Essentially, this funciton draws every Line containing at least one Block. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGrid::Render( HGE * hgeEngine ) const
{
    int LineArrayIndex = 0; 
    bool NoMoreOccupiedLines = false;

    // Render from the bottom line to the top line so that we
    // can by-pass an empty line to avoid wasting CPU cycles
    while( (LineArrayIndex < 20) && (false == NoMoreOccupiedLines) )
    {
        if( ! m_BlockLines[LineArrayIndex]->IsEmpty() )
        {
            m_BlockLines[LineArrayIndex]->Render(hgeEngine);
        }
        else
		{
            NoMoreOccupiedLines = true;
		}

        ++LineArrayIndex;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Returns the number of completed lines currently in the TetrisGrid. This algorithm searches
 * for completed lines from bottom to top. 
 *
 * @remarks This function will <b>not</b> clears the completed lines.
 * It only queries for the current number of completed lines. Call 
 * this function before TetrisGrid::ClearCompletedLines() to account for 
 * completed lines before they are cleared. 
 * 
 * @return Number of lines completed
 */
////////////////////////////////////////////////////////////////////////////////////////////
int TetrisGrid::GetLinesCompleted() const
{
    int NumberOfCompletedLines = 0;

    // This loop starts from the bottom of the grid (index 0), 
    // and traverses up the grid to the top (index 19). 
    bool AreMoreOccupiedLines = false;
    int Index = 0;

    while( (Index < 20) && (AreMoreOccupiedLines == false) )
    {                       
        // If the line is filled with blocks, we need 
        // to increament the number of completed lines
        if( m_BlockLines[Index]->IsFilled() )
        {
            ++NumberOfCompletedLines;  
            
            // This part is to help with the line deleting
            // algorithm. It "tags" the first completed line
            // so that the algorithm skips over the non-completed
            // lines below the first occurance. 
            if( NumberOfCompletedLines == 1 )
                m_FirstCompletedLineIndex = Index;
        }

        // While traversing from bottom to top of the grid we
        // encounter an empty lines, then there is NO possible
        // way a line above it contains blocks. 
        else if( m_BlockLines[Index]->IsEmpty() )
		{
            AreMoreOccupiedLines = true;
		}

        ++Index;
    }


    return NumberOfCompletedLines;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Adds the blocks from the given Tetris Block (CurrentBlock) to the TetrisGrid. 
 *
 * @remarks This function does not delete the given Tetris Block. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGrid::SnapTetrisBlockToGrid( TetrisBlock & CurrentBlock )
{
    int LineToAddBlock;
    int LinePositionToAddBlock;
    
    for(int Index = 0; Index < 4; ++Index)
    {
        LineToAddBlock          = CurrentBlock.BlockAt(Index)->GetLine();
        LinePositionToAddBlock  = CurrentBlock.BlockAt(Index)->GetLinePosition();
        
        m_BlockLines[LineToAddBlock]->AddBlock(LinePositionToAddBlock, CurrentBlock.BlockAt(Index));
    }
}

void TetrisGrid::AddBlockToGrid(Block& BlockToAdd, int Line, int Position)
{
    CPAssert( m_BlockLines[Line]->IsBlockAtPosition(Position), "Block already at that position in line" );
    CPAssert( Line < 0, "Passed in a negative line number to Grid" );
    CPAssert( Line >= TetrisGridSize, "Passed in a line number too high to Grid" );
    CPAssert( Position < 0, "Passed in a negative line nuumber to Grid" );
    CPAssert( Position >= LineSize, "Passed in a position too high to Grid" );
}

bool TetrisGrid::IsBlockAtPosition(int Line, int Position) const
{
    return m_BlockLines[Line]->IsBlockAtPosition(Position);
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Determines if the block is within the Grid
 *
 *	@return		True is the block is not outside the Grid.  
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGrid::IsBlockOutsideGrid(int Line, int Position) const
{
	bool IsTooHigh = Line >= TetrisGridSize;
	bool IsTooLow = Line < 0;
	bool IsTooFarRight = Position >= LineSize;
	bool IsTooFarLeft = Position < 0;

    return IsTooHigh || IsTooLow || IsTooFarRight || IsTooFarLeft;
}


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks if the given block will collide with another existing block
 * in the grid or is already at the bottom of the grid. 
 *
 * @return True if the block is colliding; False, otherwise. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGrid::WillCollideWithBase( TetrisBlock * CurrentBlock )
{
    bool WillCollide = false;
    
    // Check if the block is already at the bottom grid row, 
    // If true, then the block will definitely collide at the base
    bool BlockAtBottomAlready = ( (CurrentBlock->GetBottomLine() - 1) == - 1 );

    if( BlockAtBottomAlready )
	{
       WillCollide = true;
	}

    // Check if block with collide with any other existing block in the grid
    else
    {  
        int LineBelowGivenBlock = 0;
        int CurrentLinePosition = 0;

        // Check each block in the TetrisBlock for collision with line below
        int Index = 0;
        while( (false == WillCollide) && Index < 4 )
        {
            LineBelowGivenBlock = CurrentBlock->BlockAt(Index)->GetLine() - 1;
            CurrentLinePosition = CurrentBlock->BlockAt(Index)->GetLinePosition();
            
            // Make sure the line below isn't empty. Otherwise, why check to see if
            // a block will collide with a guaranteed empty space?
            if( !m_BlockLines[LineBelowGivenBlock]->IsEmpty() )
            {
                // Is there a block in the line below it?
                if( m_BlockLines[LineBelowGivenBlock]->IsBlockAtPosition(CurrentLinePosition) )
                    WillCollide = true;
            }

            ++Index;
        }
    }
    
    return WillCollide;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGrid::WillCollideWithTop( TetrisBlock * CurrentBlock )
{
    bool WillCollideWithTop = false;

    if(CurrentBlock->GetBlockType() == BlockType_I)
    {
        if( m_BlockLines[19]->IsBlockAtPosition(5) || m_BlockLines[18]->IsBlockAtPosition(5) || m_BlockLines[17]->IsBlockAtPosition(5) || 
                                                m_BlockLines[16]->IsBlockAtPosition(5) )
            WillCollideWithTop = true;
    }
    
    else
    {
        if( m_BlockLines[19]->IsBlockAtPosition(5) || m_BlockLines[18]->IsBlockAtPosition(5) )
            WillCollideWithTop = true;
    }

    return WillCollideWithTop;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks if the given block will collide with another existing block
 * in the grid on its right side or is already at the right-most position.
 *
 * @return True if the block is colliding; False, otherwise. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGrid::WillCollideWithRightWall( TetrisBlock * CurrentBlock )
{
    bool WillCollideWithRightWall = false;
    int CurrentLinePosition;
    int CurrentLine;

    // Check each block in the TetrisBlock for a collision
    int Index = 0;
    while( (false == WillCollideWithRightWall) && Index < 4 )
    {
        CurrentLinePosition = CurrentBlock->BlockAt(Index)->GetLinePosition();
        CurrentLine         = CurrentBlock->BlockAt(Index)->GetLine();
        
        // This block is at the left most position in the grid (i.e. colliding)
        if( CurrentLinePosition == RIGHT_MOST_GRID_INDEX )
            WillCollideWithRightWall = true;
            
        // TODO: Do I need this check? How much processing am I saving
        // by checking if the line is not empty? Why not just check
        // if there is a block at the next line position? 
        else if( !m_BlockLines[CurrentLine]->IsEmpty() )
        {
            if( m_BlockLines[CurrentLine]->IsBlockAtPosition(CurrentLinePosition+1) )
                WillCollideWithRightWall = true;
        }
        
        ++Index;
    }

    return WillCollideWithRightWall;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks if the given block will collide with another existing block
 * in the grid on its left side or is already at the left-most position.
 *
 * @return True if the block is colliding; False, otherwise. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGrid::WillCollideWithLeftWall( TetrisBlock * CurrentBlock )
{
    bool WillCollideWithLeftWall = false;
    int CurrentLinePosition;
    int CurrentLine;

    // Check each block in the TetrisBlock for a collision
    int Index = 0;
    while( (false == WillCollideWithLeftWall) && (Index < 4) )
    {
        CurrentLinePosition = CurrentBlock->BlockAt(Index)->GetLinePosition();
        CurrentLine         = CurrentBlock->BlockAt(Index)->GetLine();
        
        // This block is at the left most position in the grid (i.e. colliding)
        if( CurrentLinePosition == LEFT_MOST_GRID_INDEX )
            WillCollideWithLeftWall = true;
            
        // TODO: Do I need this check? How much processing am I saving
        // by checking if the line is not empty? Why not just check
        // if there is a block at the next line position? 
        else if( !m_BlockLines[CurrentLine]->IsEmpty() )
        {
            if( m_BlockLines[CurrentLine]->IsBlockAtPosition(CurrentLinePosition-1) )
                WillCollideWithLeftWall = true;
        }
        
        ++Index;
    }

    return WillCollideWithLeftWall;
}

bool TetrisGrid::WillCollideWithGrid( TetrisBlock * CurrentBlock )
{
    return ( WillCollideWithTop(CurrentBlock) || WillCollideWithBase(CurrentBlock) || 
        WillCollideWithLeftWall(CurrentBlock) || WillCollideWithRightWall(CurrentBlock) );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Clears the entire line at the given index of all blocks. 
 *
 * @param   Index   The index of the line to clear. Must be between 0 and TetrisGridSize, 
 *                  inclusively. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGrid::ClearLine( int Index )
{
    CPAssert( Index > -1 && Index < 20, "Invalid Index in TetrisGrid::ClearLine()" );

    m_BlockLines[Index]->Clear();
    delete m_BlockLines[Index];
    m_BlockLines[Index] = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Handles the situation where at least one line was completed. This involves shifting
 * the lines down by the number of lines completed and generating new lines at the top
 * of the TetrisGrid. 
 *
 * @param   EventRecord     Important variables pertaining to handling a completed line event. 
 *
 * @ToDo    Recycle Cleared Line to top (pointer copying) instead of instantiating new Lines. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGrid::OnLineComplete( const CompletedLineEvent & EventRecord )
{       
    int LineToMoveDownIndex = EventRecord.InitialLineToShiftDown;
    int LinesCompleted = EventRecord.LinesCompleted;
    Line * CurrentLine = NULL;

    CPAssert( LinesCompleted < 5 || LinesCompleted > 0, "Invalid Number of Lines Completed in TetrisGrid::OnLineComplete");
    CPAssert( LineToMoveDownIndex > 0 && LineToMoveDownIndex < TetrisGridSize, "Invalid InitialLineToShiftDown in TetrisGrid::OnLineComplete");
    CPAssert( (LineToMoveDownIndex - LinesCompleted) > -1, "Line will shift down below array index zero (out of bound) in TetrisGrid::OnLineComplete");

    // Move Blocks Down
    for( LineToMoveDownIndex; LineToMoveDownIndex < TetrisGridSize; ++LineToMoveDownIndex )
    {
        CurrentLine = m_BlockLines[LineToMoveDownIndex];
        CurrentLine->SubtractLineIndex(LinesCompleted);
        m_BlockLines[LineToMoveDownIndex - LinesCompleted] =  m_BlockLines[LineToMoveDownIndex];
    }

    // Create new lines at the top of the TetrisGrid to compensate for the cleared lines.
    for( int NewLineIndex = TetrisGridSize - LinesCompleted; NewLineIndex < TetrisGridSize; ++NewLineIndex )
        m_BlockLines[NewLineIndex] = new Line();

#if defined TETRIS_GRID_LOG
        LogCompletedEvent(EventRecord);
#endif
}


#if defined TETRIS_GRID_LOG
void TetrisGrid::DebugRender( bool BeforeLineDelete ) const
{
    HGE * hgeEngine = GetEngine();

    BeforeLineDelete ? hgeEngine->System_Log("Before") : hgeEngine->System_Log("After");

    hgeEngine->System_Log( "   Grid Indicies   " );
    hgeEngine->System_Log( "0 1 2 3 4 5 6 7 8 9" );

    for( int LineIndex = GridSize - 1; LineIndex > -1; --LineIndex )
    {
        CPString LineString(LineSize * 2);
        int OffsetIndex = 0;

        for( int BlockIndex = 0; BlockIndex < LineSize; ++BlockIndex )
        {
            OffsetIndex = BlockIndex * 2;

            if( m_BlockLines[LineIndex]->BlockAtIndex(BlockIndex) )
            {
                LineString[OffsetIndex] = 'X';
                LineString[OffsetIndex + 1] = ' ';
            }
            else
            {
                LineString[OffsetIndex] = '-';
                LineString[OffsetIndex + 1] = ' ';
            }
        }
        
        hgeEngine->System_Log( LineString.GetString() );
    }

    hgeEngine->System_Log( "" );
}

void TetrisGrid::LogCompletedEvent( const CompletedLineEvent & EventRecord )
{
    HGE * hgeEngine = GetEngine();

    hgeEngine->System_Log( "## AT LEAST ONE LINE WAS SUCCESSFULLY CREATED ##" );
    hgeEngine->System_Log( "Lines Completed:            %d", EventRecord.LinesCompleted );
    hgeEngine->System_Log( "Initial Line To Shift Down: %d", EventRecord.InitialLineToShiftDown );
    hgeEngine->System_Log( "" );
}
#endif
