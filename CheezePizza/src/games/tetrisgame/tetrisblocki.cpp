#include "tetrisblocki.h"
#include "tetrisblockproxy.h"
#include "block.h"



TetrisBlockI::TetrisBlockI( float TopLeftPositionX, float TopLeftPositionY )
{
    // initializes all the x and y-coordinates
    m_Blocks[0]->SetX(TopLeftPositionX);
    m_Blocks[0]->SetY(TopLeftPositionY);
    m_Blocks[1]->SetX(TopLeftPositionX);
    m_Blocks[1]->SetY(TopLeftPositionY+17);
    m_Blocks[2]->SetX(TopLeftPositionX);
    m_Blocks[2]->SetY(TopLeftPositionY+34);
    m_Blocks[3]->SetX(TopLeftPositionX);
    m_Blocks[3]->SetY(TopLeftPositionY+51);
        
    // initializes the line value
    m_Blocks[0]->SetLine(19);
    m_Blocks[1]->SetLine(18);
    m_Blocks[2]->SetLine(17);
    m_Blocks[3]->SetLine(16);
    
    
    // initializes the line position
    m_Blocks[0]->SetLinePosition(5);
    m_Blocks[1]->SetLinePosition(5);
    m_Blocks[2]->SetLinePosition(5);
    m_Blocks[3]->SetLinePosition(5);
    
    // sets the color of the blocks
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->SetColor(YELLOW);
    }
    
    m_BlockType = BlockType_I;
}

TetrisBlockI::~TetrisBlockI()
{
}

int TetrisBlockI::GetBottomLine() const
{
    int BottomLine = m_Blocks[3]->GetLine();
    
    return BottomLine; 
}

void TetrisBlockI::SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy)
{
    switch( Rotation % 2 )
    {
    case 1:
		{
			OutProxy.Proxies[0].Position.X += 17;
			OutProxy.Proxies[0].Position.Y -= 17;
			OutProxy.Proxies[0].Line += 1;
	    
			OutProxy.Proxies[2].Position.X -= 17;
			OutProxy.Proxies[2].Position.Y += 17;
			OutProxy.Proxies[2].Line -= 1;
	        
			OutProxy.Proxies[3].Position.X -= 34;
			OutProxy.Proxies[3].Position.Y += 34;
			OutProxy.Proxies[3].Line -= 2;
	        
			int NewLinePosition = OutProxy.Proxies[1].LinePosition;
			OutProxy.Proxies[0].LinePosition = NewLinePosition;
			OutProxy.Proxies[2].LinePosition = NewLinePosition;
			OutProxy.Proxies[3].LinePosition = NewLinePosition;
        
			break;
		}

    case 0:
		{
			int NewLine = OutProxy.Proxies[1].Line;

			OutProxy.Proxies[0].Position.X -= 17;
			OutProxy.Proxies[0].Position.Y += 17;
			OutProxy.Proxies[0].Line = NewLine;
	    
			OutProxy.Proxies[2].Position.X += 17;
			OutProxy.Proxies[2].Position.Y -= 17;
			OutProxy.Proxies[2].Line = NewLine;
	        
			OutProxy.Proxies[3].Position.X += 34;
			OutProxy.Proxies[3].Position.Y -= 34;
			OutProxy.Proxies[3].Line = NewLine;
	        
			int BaseLinePosition = OutProxy.Proxies[1].LinePosition;
			OutProxy.Proxies[0].LinePosition = BaseLinePosition - 1;
			OutProxy.Proxies[2].LinePosition = BaseLinePosition + 1;
			OutProxy.Proxies[3].LinePosition = BaseLinePosition + 2;
	        
			break;
		}

    default:
        break;
    }
}

// EOF
