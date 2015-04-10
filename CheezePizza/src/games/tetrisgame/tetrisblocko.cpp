#include "tetrisblocko.h"
#include "tetrisblockproxy.h"
#include "block.h"


TetrisBlockO::TetrisBlockO( float TopLeftPositionX, float TopLeftPositionY )
{
    // initializes all the x and y-coordinates
    m_Blocks[0]->SetX( TopLeftPositionX );
    m_Blocks[0]->SetY( TopLeftPositionY );
    m_Blocks[1]->SetX( TopLeftPositionX + 17 );
    m_Blocks[1]->SetY( TopLeftPositionY );
    m_Blocks[2]->SetX( TopLeftPositionX + 17 );
    m_Blocks[2]->SetY( TopLeftPositionY + 17 );
    m_Blocks[3]->SetX( TopLeftPositionX );
    m_Blocks[3]->SetY( TopLeftPositionY + 17 );
        
    // initializes the line value
    m_Blocks[0]->SetLine(19);
    m_Blocks[1]->SetLine(19);
    m_Blocks[2]->SetLine(18);
    m_Blocks[3]->SetLine(18);
    
    // initializes the line position
    m_Blocks[0]->SetLinePosition(5);
    m_Blocks[1]->SetLinePosition(6);
    m_Blocks[2]->SetLinePosition(6);
    m_Blocks[3]->SetLinePosition(5);
    
    // sets the color of the blocks
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->SetColor(WHITE);
    }
    
    m_BlockType = BlockType_O;
}

TetrisBlockO::~TetrisBlockO()
{
}

int TetrisBlockO::GetBottomLine() const
{
    int BottomLine = m_Blocks[2]->GetLine();
    
    return BottomLine; 
}

void TetrisBlockO::SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy)
{
}

// EOF
