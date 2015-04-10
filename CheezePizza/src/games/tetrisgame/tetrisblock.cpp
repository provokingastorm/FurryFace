#include "tetrisblock.h"
#include "tetrisblockproxy.h"
#include "tetrisgrid.h"
#include "block.h"


TetrisBlock::TetrisBlock()
:x(0),
y(0),
m_Rotation(1),
m_BlockType(BlockType_None)
{
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i] = new Block( 0, 0 );
    }
}

TetrisBlock::TetrisBlock( float TopLeftPositionX, float TopLeftPositionY )
:x(325),
y(91),
m_Rotation(1),
m_BlockType(BlockType_None)
{
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i] = new Block( TopLeftPositionX, TopLeftPositionY );
    }
}


TetrisBlock::~TetrisBlock()
{
    /*
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        if(m_Blocks[i] != 0)
        {
            delete m_Blocks[i];
            m_Blocks[i] = 0;
        }
    }*/    
}

/***********************************************************
 * Returns a pointer to the Block object at the given index. 
 *
 * @remarks If the input is invalid (Index is < 0 or Index > 3,
 * this function will return a NULL pointer. 
 *
 * @param Index Index of the Block in the TetrisBlock (Range: 0 - 3)
 *
 * @return A pointer to desired block (assuming the Index is valid)
 *
 * @author Peter Bennett (curlyhairedgreatness@gmail.com)
 ************************************************************/
Block* TetrisBlock::BlockAt(int Index)
{
    Block * BlockAtGivenIndex = 0;

    if( (Index >= 0) || (Index <= 3) )
        BlockAtGivenIndex = m_Blocks[Index];

    return BlockAtGivenIndex;
}
void TetrisBlock::Render( HGE * hgeEngine ) const
{
    for( int Index = 0; Index < TetrisBlockSize; ++Index )
        m_Blocks[Index]->Render( hgeEngine );
}
/***********************************************************
 * updates the x-coordinate of the blocks such that on the 
 * next draw, the block will be shifted 17 pixels left
 ************************************************************/
void TetrisBlock::MoveLeft()
{
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->MoveLeft();
    }
}

/***********************************************************
 * updates the y-coordinate of the blocks such that on the 
 * next draw, the block will be shifted 17 pixels right
 ************************************************************/
void TetrisBlock::MoveRight()
{
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->MoveRight();
    }
}

/**
 * Updates the X-coordinate  and Y-coordinate of the blocks such
 * that on the next draw, the block will be shifted 17 pixels left
 *
 * @author Peter Bennett (curlyhairedgreatness@gmail.com)
 */
void TetrisBlock::MoveDown()
{   
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        if(m_Blocks[i]->GetLine() > 0)
                m_Blocks[i]->MoveDown();
    }
}
/***********************************************************
 * updates the line value of the blocks if the block is in boundaries
 ************************************************************/
void TetrisBlock::UpdateLine()
{
    
        for(int i = 0; i < TetrisBlockSize; i++)
        {
            if(m_Blocks[i]->GetLine() > 0 && m_Blocks[i]->GetLine()< 20)
			{
                m_Blocks[i]->UpdateLine();
			}
        }
}

void TetrisBlock::Rotate()
{
    m_Rotation++;
    TetrisBlockProxy RotatedProxy(m_Blocks);
    SimulateRotation(m_Rotation, RotatedProxy);

    for( int ProxyIndex = 0; ProxyIndex < TetrisBlockSize; ++ProxyIndex )
    {
        m_Blocks[ProxyIndex]->SetX( RotatedProxy.Proxies[ProxyIndex].Position.X );
        m_Blocks[ProxyIndex]->SetY( RotatedProxy.Proxies[ProxyIndex].Position.Y );
        m_Blocks[ProxyIndex]->SetLine( RotatedProxy.Proxies[ProxyIndex].Line );
        m_Blocks[ProxyIndex]->SetLinePosition( RotatedProxy.Proxies[ProxyIndex].LinePosition );
    }
}

void TetrisBlock::AddBlocksToGrid( TetrisGrid & Grid )
{
    for( int BlockIndex = 0; BlockIndex < TetrisBlockSize; ++BlockIndex )
    {
#pragma message("m_Blocks needs a deference")
        Grid.AddBlockToGrid( *(m_Blocks[BlockIndex]), m_Blocks[BlockIndex]->GetLine(), m_Blocks[BlockIndex]->GetLinePosition() );
    }
}

bool TetrisBlock::CanRotate(const TetrisGrid& InGrid)
{
    TetrisBlockProxy RotatedProxy(m_Blocks);
    SimulateRotation(m_Rotation + 1, RotatedProxy);

    return RotatedProxy.WillBlocksCollideWithGrid(InGrid);
}



