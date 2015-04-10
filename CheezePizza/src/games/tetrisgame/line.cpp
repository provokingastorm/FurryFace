#include "line.h"
#include "block.h"
#include "debugutilities.h"
#include "point.h"




////////////////////////////////////////////////////////////////////////////////////////////
// Default Constructor
////////////////////////////////////////////////////////////////////////////////////////////
Line::Line()
    :   m_iActiveBlockCount(0)
    ,   Position(*(new Point()))
{
    for( int Index = 0; Index < LineSize; ++Index )
    {
        m_Blocks[Index] = 0;
    } 
}

////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////
Line::~Line()
{
    for( int Index = 0; Index < LineSize; ++Index )
    {
        if( m_Blocks[Index] )
            delete m_Blocks[Index]; 
    }
    
}

void Line::Render( HGE * hgeEngine ) const
{
    for( int Index = 0; Index < LineSize; ++Index )
    {
        if( m_Blocks[Index] != NULL )
            m_Blocks[Index]->Render(hgeEngine);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks to see if the line is filled.
 *
 * @return TRUE if the lines has a Block residing in each spot. 
 * FALSE, otherwise. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool Line::IsFilled() const
{        
    return ( m_iActiveBlockCount == LineSize );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Removes all blocks currently residing in the line. 
 *
 * @remarks This is a useful alternative to dynamically allocating a 
 * new line. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void Line::Clear()
{
    for( int Index = 0; Index < LineSize; ++Index )
    {
        RemoveBlock(Index);
    }
    
    m_iActiveBlockCount = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Returns whether or not the Line is empty.
 * 
 * @return TRUE if the lines has no blocks residing in it. 
 * FALSE, otherweise. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool Line::IsEmpty() const
{
    return ( m_iActiveBlockCount == 0 );
}


bool Line::CanAddBlockToLine(const Block& BlockToAdd) const
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks if there is a block in the line at the given index.
 *
 * @param Index The index of the Line. Index is valid for values between zero and LineSize - 1.
 * @return true if the index is valid and there is a Block stored at the given index.
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool Line::IsBlockAtPosition(int Position) const
{    
    CPAssert( Position >= 0, "Passed in a negative position to Line" );
    CPAssert( Position < LineSize, "Passed in a position too high to Line" );

    bool BlockExistsAtIndex = false;

    if( Position >= 0 && Position < LineSize )
    {
        if ( m_Blocks[Position] != 0 )
                BlockExistsAtIndex = true;
    }

    return BlockExistsAtIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Removes block from the line at the given index. 
 * 
 * @param Index The index of the Line (from 0 to LineSize)
 */
////////////////////////////////////////////////////////////////////////////////////////////
void Line::RemoveBlock(int Index)
{
    if( IsBlockAtPosition(Index) )
    {
        delete m_Blocks[Index]; 
        m_Blocks[Index] = 0;

        // Since we are removing a block from the line, 
        // update the block number counter
        m_iActiveBlockCount--;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Adds the given block at the given index in the line. 
 * 
 * @param Index The index of the Line (from 0 to LineSize)
 * @param inBlock A pointer to the existing Block to be stored in the Line. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void Line::AddBlock( int Index, Block * inBlock )
{
    if (!IsBlockAtPosition(Index))
    {
        m_Blocks[Index] = inBlock;
        // since we are adding a block to the line, 
        // update the block number counter
        m_iActiveBlockCount++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Subtracts the Line Index value of all blocks in the line by the given amount.
 * 
 * @param   TotalIndicies   The number of indicies to subtract for each Line Index.
 */
////////////////////////////////////////////////////////////////////////////////////////////
void Line::SubtractLineIndex( int TotalIndicies )
{
    for( int Index = 0; Index < LineSize; ++Index )
    {
        if( m_Blocks[Index] )
            m_Blocks[Index]->MoveDown( TotalIndicies );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Converts the Block's screen position into an array index (i.e. line position)
 *
 *  The returning line index should never be negative or larger than the total block 
 *  positions available. 
 * 
 * @param   InBlock   The block that determines the index
 */
////////////////////////////////////////////////////////////////////////////////////////////
int Line::GetLinePosition(const Block& InBlock)
{
    int LineIndex = 0;

    LineIndex = (Position.X - InBlock.GetX()) / InBlock.GetWidth();

    CPAssert( LineIndex < 0,            "Converting Block Position into Line Index resulted in a negative index");
    CPAssert( LineIndex >= LineSize,    "Converting Block Position into Line Index resulted in an index too large");

    return LineIndex;
}

// EOF
