#include "block.h"

/**
 * Constructor
 */
Block::Block( float TopLeftX, float TopLeftY )
: m_BlockQuad(), 
  m_iWidth(BLOCK_WIDTH), 
  m_iHeight(BLOCK_HEIGHT), 
  m_iLineIndex(20), 
  m_iLinePosition(5), 
  m_Color(BLUE)
{
    m_BlockQuad.tex = 0;

    m_BlockQuad.v[0].x = TopLeftX;
    m_BlockQuad.v[0].y = TopLeftY;

    m_BlockQuad.v[1].x = TopLeftX + m_iWidth;
    m_BlockQuad.v[1].y = TopLeftY;

    m_BlockQuad.v[2].x = TopLeftX + m_iWidth;
    m_BlockQuad.v[2].y = TopLeftY + m_iHeight;
    
    m_BlockQuad.v[3].x = TopLeftX;
    m_BlockQuad.v[3].y = TopLeftY + m_iHeight;

    for( int Index = 0; Index < 4; ++Index )
    {
		m_BlockQuad.v[Index].col = m_Color;
    }
}

/**
 * Destructor
 */
Block::~Block()
{
}
/**
 * changes the y-coordinate so that the block
 * will move down one block length on the next rasterization
 */
void Block::MoveDown()
{    
    m_BlockQuad.v[0].y += 17;
    m_BlockQuad.v[1].y += 17;
    m_BlockQuad.v[2].y += 17;
    m_BlockQuad.v[3].y += 17;
    m_iLineIndex--;
}

void Block::MoveDown( int LineIndicies )
{    
    int PixelsToAdd = LineIndicies * 17;

    m_BlockQuad.v[0].y += PixelsToAdd;
    m_BlockQuad.v[1].y += PixelsToAdd;
    m_BlockQuad.v[2].y += PixelsToAdd;
    m_BlockQuad.v[3].y += PixelsToAdd;
    m_iLineIndex -= LineIndicies;
}

/**
 * changes the x-coordinate so that the block
 * will move left one block length on the next rasterization
 */
void Block::MoveLeft()
{
    m_BlockQuad.v[0].x -= 17;
    m_BlockQuad.v[1].x -= 17;
    m_BlockQuad.v[2].x -= 17;
    m_BlockQuad.v[3].x -= 17;
    m_iLinePosition--;
}
/**
 * changes the x-coordinate so that the block
 * will move right one block length on the next rasterization
 */
void Block::MoveRight()
{
    m_BlockQuad.v[0].x += 17;
    m_BlockQuad.v[1].x += 17;
    m_BlockQuad.v[2].x += 17;
    m_BlockQuad.v[3].x += 17;
    m_iLinePosition++;
}


void Block::Render( HGE * hgeEngine ) const
{
    hgeEngine->Gfx_RenderQuad( &m_BlockQuad );
}

void Block::CopyInto( Block & outBlock )
{
    outBlock.SetX( m_BlockQuad.v[0].x );
    outBlock.SetY( m_BlockQuad.v[0].y );
    outBlock.SetLinePosition( m_iLinePosition );
    outBlock.SetLine( m_iLineIndex );
    outBlock.SetColor( m_Color );
}

void Block::SetColor(DWORD Color)
{
    for( int Index = 0; Index < 4; ++Index )
        m_BlockQuad.v[Index].col = Color; 
}
